//! WiFi and API communication task
//! 
//! Handles WiFi connection, maintains network state, and communicates with the API.

use embassy_net::{Config, Stack, StackResources};
use embassy_time::{Duration, Timer};
use esp_hal::{peripherals::WIFI, timer::timg::TimerGroup};
use esp_wifi::{
    wifi::{
        ClientConfiguration, Configuration, WifiController, WifiDevice, WifiEvent, WifiStaDevice,
        WifiState,
    },
    EspWifiInitFor,
};
use defmt::*;

use crate::config::{WIFI_CONNECT_TIMEOUT_SECS, API_TIMEOUT_SECS};
use super::led::{LedCommand, StatusColor, LED_COMMANDS};

/// WiFi credentials (in production, load from NVS)
const WIFI_SSID: &str = "YOUR_WIFI_SSID";
const WIFI_PASSWORD: &str = "YOUR_WIFI_PASSWORD";

/// API endpoint (in production, load from NVS)
const API_ENDPOINT: &str = "https://your-api.example.com";

/// WiFi + API task
#[embassy_executor::task]
pub async fn wifi_task(
    wifi_peripheral: WIFI,
    clocks: &'static esp_hal::clock::Clocks<'static>,
    timer_group: TimerGroup<'static>,
) {
    info!("WiFi task started");
    
    // Indicate connecting state
    LED_COMMANDS.signal(LedCommand::SetStatus(StatusColor::Blue));
    
    // Initialize WiFi
    let init = esp_wifi::initialize(
        EspWifiInitFor::Wifi,
        timer_group.timer0,
        esp_hal::rng::Rng::new(peripherals.RNG),
        peripherals.RADIO_CLK,
        clocks,
    )
    .unwrap();
    
    let wifi = wifi_peripheral;
    let (wifi_interface, controller) =
        esp_wifi::wifi::new_with_mode(&init, wifi, WifiStaDevice).unwrap();
    
    // Configure WiFi
    let config = Configuration::Client(ClientConfiguration {
        ssid: WIFI_SSID.try_into().unwrap(),
        password: WIFI_PASSWORD.try_into().unwrap(),
        ..Default::default()
    });
    
    let mut controller = controller;
    controller.set_configuration(&config).unwrap();
    
    info!("Starting WiFi controller");
    controller.start().await.unwrap();
    
    // Connect to WiFi
    info!("Connecting to WiFi: {}", WIFI_SSID);
    let timeout = Duration::from_secs(WIFI_CONNECT_TIMEOUT_SECS);
    
    match embassy_time::with_timeout(timeout, controller.connect()).await {
        Ok(Ok(_)) => {
            info!("WiFi connected!");
            LED_COMMANDS.signal(LedCommand::SetStatus(StatusColor::Green));
        }
        Ok(Err(e)) => {
            error!("WiFi connection failed: {:?}", e);
            LED_COMMANDS.signal(LedCommand::SetStatus(StatusColor::Yellow));
            return;
        }
        Err(_) => {
            error!("WiFi connection timeout");
            LED_COMMANDS.signal(LedCommand::SetStatus(StatusColor::Yellow));
            return;
        }
    }
    
    // Wait for IP address
    info!("Waiting for IP address...");
    controller.wait_for_event(WifiEvent::StaConnected).await;
    
    // Set up network stack (for future HTTP requests)
    let seed = 1234; // In production, use hardware RNG
    let stack_config = Config::dhcpv4(Default::default());
    
    static STACK_RESOURCES: StaticCell<StackResources<3>> = StaticCell::new();
    let resources = STACK_RESOURCES.init(StackResources::new());
    
    static STACK: StaticCell<Stack<WifiDevice<'_, WifiStaDevice>>> = StaticCell::new();
    let stack = STACK.init(Stack::new(
        wifi_interface,
        stack_config,
        resources,
        seed,
    ));
    
    // Spawn network task
    spawner.spawn(net_task(stack)).ok();
    
    // Wait for IP
    loop {
        if stack.is_config_up() {
            info!("Network configured!");
            break;
        }
        Timer::after(Duration::from_millis(100)).await;
    }
    
    if let Some(config) = stack.config_v4() {
        info!("IP Address: {}", config.address);
    }
    
    // Main API communication loop
    loop {
        // Handle button events and make API calls
        if let Ok(event) = embassy_time::with_timeout(
            Duration::from_secs(1),
            crate::tasks::button::BUTTON_EVENTS.wait()
        ).await {
            match event {
                crate::tasks::button::ButtonEvent::ShortPress => {
                    info!("Handling clock in/out");
                    handle_clock_toggle(stack).await;
                }
                crate::tasks::button::ButtonEvent::LongPress => {
                    info!("Handling long press (config mode?)");
                    LED_COMMANDS.signal(LedCommand::Rainbow);
                }
            }
        }
        
        Timer::after(Duration::from_millis(100)).await;
    }
}

/// Network task for embassy-net
#[embassy_executor::task]
async fn net_task(stack: &'static Stack<WifiDevice<'static, WifiStaDevice>>) {
    stack.run().await
}

/// Handle clock in/out API call
async fn handle_clock_toggle(stack: &Stack<WifiDevice<'_, WifiStaDevice>>) {
    info!("Making API request to {}", API_ENDPOINT);
    
    LED_COMMANDS.signal(LedCommand::SetStatus(StatusColor::Purple));
    
    // TODO: Implement HTTP request using reqwless
    // This is a placeholder for the actual HTTP client implementation
    
    Timer::after(Duration::from_secs(1)).await;
    
    // Simulate success
    info!("API request successful");
    LED_COMMANDS.signal(LedCommand::SetStatus(StatusColor::Green));
    
    // Update energy meter (example: 5/7 hours remaining)
    LED_COMMANDS.signal(LedCommand::SetEnergyMeter(5));
}

// Note: StaticCell is needed for static allocation
use static_cell::StaticCell;
use embassy_executor::Spawner;
