//! LED control task for WS2812B addressable RGB LEDs
//! 
//! Manages status LED and energy meter display using smart-leds and RMT peripheral.

use embassy_sync::{blocking_mutex::raw::CriticalSectionRawMutex, signal::Signal};
use embassy_time::{Duration, Timer};
use esp_hal::{
    gpio::OutputPin,
    rmt::{PulseCode, TxChannel, TxChannelConfig, TxChannelCreator},
    Blocking,
};
use smart_leds::{
    brightness, gamma,
    hsv::{hsv2rgb, Hsv},
    SmartLedsWrite, RGB8,
};
use defmt::*;

use crate::config::{LED_BRIGHTNESS, NUM_LEDS};

/// LED colors for status indication
#[derive(Debug, Clone, Copy, PartialEq)]
pub enum StatusColor {
    Red,      // Clocked out
    Green,    // Clocked in
    Blue,     // WiFi connecting
    Yellow,   // API error
    Purple,   // Charging
    Off,      // Off
}

impl StatusColor {
    fn to_rgb(self) -> RGB8 {
        match self {
            StatusColor::Red => RGB8::new(255, 0, 0),
            StatusColor::Green => RGB8::new(0, 255, 0),
            StatusColor::Blue => RGB8::new(0, 0, 255),
            StatusColor::Yellow => RGB8::new(255, 255, 0),
            StatusColor::Purple => RGB8::new(128, 0, 128),
            StatusColor::Off => RGB8::new(0, 0, 0),
        }
    }
}

/// LED command for updating the display
#[derive(Debug, Clone, Copy)]
pub enum LedCommand {
    SetStatus(StatusColor),
    SetEnergyMeter(u8), // 0-7 LEDs lit
    Rainbow,            // Demo mode
}

/// Global signal for LED commands
pub static LED_COMMANDS: Signal<CriticalSectionRawMutex, LedCommand> = Signal::new();

/// WS2812B LED strip driver using RMT
struct Ws2812<'d> {
    channel: TxChannel<'d, Blocking, 0>,
}

impl<'d> Ws2812<'d> {
    fn new<P: OutputPin>(pin: P, channel: impl TxChannelCreator<'d, 0>) -> Self {
        let config = TxChannelConfig {
            clk_divider: 1,
            ..TxChannelConfig::default()
        };
        
        let channel = channel.configure(pin, config).unwrap();
        
        Self { channel }
    }
    
    fn write_pixels(&mut self, pixels: &[RGB8]) {
        // Convert RGB to RMT pulses (WS2812B timing)
        let mut pulses = heapless::Vec::<PulseCode, 512>::new();
        
        for pixel in pixels {
            // GRB order for WS2812B
            let colors = [pixel.g, pixel.r, pixel.b];
            
            for color in colors {
                for bit in (0..8).rev() {
                    let high = (color >> bit) & 1 == 1;
                    let pulse = if high {
                        PulseCode {
                            level1: true,
                            length1: 32, // 0.8us high
                            level2: false,
                            length2: 14, // 0.35us low
                        }
                    } else {
                        PulseCode {
                            level1: true,
                            length1: 14, // 0.35us high
                            level2: false,
                            length2: 32, // 0.8us low
                        }
                    };
                    
                    pulses.push(pulse).ok();
                }
            }
        }
        
        // Send pulses
        self.channel.transmit(&pulses).wait().ok();
    }
}

/// LED control task
#[embassy_executor::task]
pub async fn led_task<P: OutputPin>(pin: P, channel: impl TxChannelCreator<'static, 0>) {
    info!("LED task started");
    
    let mut ws2812 = Ws2812::new(pin, channel);
    let mut pixels = [RGB8::default(); NUM_LEDS];
    
    // Initial state: blue (connecting)
    pixels[0] = StatusColor::Blue.to_rgb();
    ws2812.write_pixels(&pixels);
    
    let mut energy_level: u8 = 0;
    let mut status_color = StatusColor::Blue;
    
    loop {
        // Check for commands
        if let Ok(cmd) = embassy_time::with_timeout(
            Duration::from_millis(100),
            LED_COMMANDS.wait()
        ).await {
            match cmd {
                LedCommand::SetStatus(color) => {
                    debug!("LED: Setting status to {:?}", color);
                    status_color = color;
                    pixels[0] = color.to_rgb();
                }
                LedCommand::SetEnergyMeter(level) => {
                    debug!("LED: Setting energy meter to {}/7", level);
                    energy_level = level.min(7);
                    
                    // Update energy meter LEDs (1-7)
                    for i in 1..NUM_LEDS {
                        if i <= energy_level as usize {
                            // Green to yellow gradient based on remaining energy
                            let hue = 120 - (i as u8 * 15); // 120=green, 60=yellow
                            let color = hsv2rgb(Hsv {
                                hue,
                                sat: 255,
                                val: LED_BRIGHTNESS,
                            });
                            pixels[i] = color;
                        } else {
                            pixels[i] = RGB8::new(0, 0, 0);
                        }
                    }
                }
                LedCommand::Rainbow => {
                    debug!("LED: Rainbow mode");
                    // Animate rainbow effect
                    for hue in 0..=255 {
                        for (i, pixel) in pixels.iter_mut().enumerate() {
                            let h = hue.wrapping_add((i as u8) * 32);
                            *pixel = hsv2rgb(Hsv {
                                hue: h,
                                sat: 255,
                                val: LED_BRIGHTNESS / 2,
                            });
                        }
                        
                        let adjusted = brightness(gamma(pixels.iter().cloned()), LED_BRIGHTNESS);
                        ws2812.write_pixels(&adjusted.collect::<heapless::Vec<_, 8>>().as_slice());
                        
                        Timer::after(Duration::from_millis(10)).await;
                    }
                    
                    // Restore state
                    pixels[0] = status_color.to_rgb();
                    continue;
                }
            }
            
            // Apply brightness and gamma correction
            let adjusted = brightness(gamma(pixels.iter().cloned()), LED_BRIGHTNESS);
            ws2812.write_pixels(&adjusted.collect::<heapless::Vec<_, 8>>().as_slice());
        }
        
        Timer::after(Duration::from_millis(50)).await;
    }
}
