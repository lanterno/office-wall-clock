//! Button handling task with async debouncing and long-press detection
//! 
//! Uses Embassy's async capabilities for clean, non-blocking button handling.

use embassy_sync::{blocking_mutex::raw::CriticalSectionRawMutex, signal::Signal};
use embassy_time::{Duration, Instant, Timer};
use esp_hal::gpio::{Input, Pin, PullUp};
use defmt::*;

use crate::config::{BUTTON_DEBOUNCE_MS, BUTTON_LONG_PRESS_MS};

/// Button events that can be sent to other tasks
#[derive(Debug, Clone, Copy, PartialEq)]
pub enum ButtonEvent {
    ShortPress,
    LongPress,
}

/// Global signal for button events (accessible by other tasks)
pub static BUTTON_EVENTS: Signal<CriticalSectionRawMutex, ButtonEvent> = Signal::new();

/// Button task - handles debouncing and press detection
#[embassy_executor::task]
pub async fn button_task(mut button: Input<'static>) {
    info!("Button task started");
    
    let mut last_press_time = Instant::now();
    let mut press_start: Option<Instant> = None;
    
    loop {
        // Wait for button press (falling edge - active low)
        button.wait_for_falling_edge().await;
        
        let now = Instant::now();
        
        // Debounce: ignore if too soon after last press
        if now.duration_since(last_press_time).as_millis() < BUTTON_DEBOUNCE_MS {
            continue;
        }
        
        // Record press start time
        press_start = Some(now);
        debug!("Button pressed");
        
        // Wait for release or long-press timeout
        loop {
            Timer::after(Duration::from_millis(50)).await;
            
            if button.is_high() {
                // Button released
                let press_duration = now.elapsed();
                
                if press_duration.as_millis() >= BUTTON_LONG_PRESS_MS {
                    info!("Long press detected ({}ms)", press_duration.as_millis());
                    BUTTON_EVENTS.signal(ButtonEvent::LongPress);
                } else {
                    info!("Short press detected ({}ms)", press_duration.as_millis());
                    BUTTON_EVENTS.signal(ButtonEvent::ShortPress);
                }
                
                last_press_time = now;
                break;
            }
            
            // Check for long press while still held
            if press_start.is_some() && now.elapsed().as_millis() >= BUTTON_LONG_PRESS_MS {
                info!("Long press detected (held)");
                BUTTON_EVENTS.signal(ButtonEvent::LongPress);
                
                // Wait for release
                button.wait_for_rising_edge().await;
                last_press_time = Instant::now();
                break;
            }
        }
    }
}
