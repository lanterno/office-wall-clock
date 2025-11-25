//! WiFi and API communication task
//! 
//! Handles WiFi connection, maintains network state, and communicates with the API.

use core::fmt::Write as FmtWrite;

use embassy_net::{tcp::TcpSocket, Config, IpEndpoint, Stack, StackResources};
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
use embedded_io_async::Write as AsyncWrite;

use crate::config::{NetworkConfig, NETWORK_CONFIG, WIFI_CONNECT_TIMEOUT_SECS, API_RETRY_COUNT, API_TIMEOUT_SECS};
use super::led::{LedCommand, StatusColor, LED_COMMANDS};

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
    
    // Configure WiFi from compile-time configuration
    let config = Configuration::Client(ClientConfiguration {
        ssid: NETWORK_CONFIG.wifi_ssid.try_into().unwrap(),
        password: NETWORK_CONFIG.wifi_password.try_into().unwrap(),
        ..Default::default()
    });
    
    let mut controller = controller;
    controller.set_configuration(&config).unwrap();
    
    info!("Starting WiFi controller");
    controller.start().await.unwrap();
    
    // Connect to WiFi
    info!("Connecting to WiFi: {}", NETWORK_CONFIG.wifi_ssid);
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
                    if let Err(e) = handle_clock_toggle(stack, &NETWORK_CONFIG).await {
                        warn!("API toggle failed: {}", e);
                        LED_COMMANDS.signal(LedCommand::SetStatus(StatusColor::Yellow));
                    }
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

/// Handle clock in/out API call.
///
/// This is a **very small HTTP client** built directly on `embassy-net`'s
/// `TcpSocket`. It sends a `POST` request with an empty body to the configured
/// `api_path` and treats any successful TCP exchange as a success.
async fn handle_clock_toggle(
    stack: &Stack<WifiDevice<'_, WifiStaDevice>>,
    cfg: &NetworkConfig,
) -> Result<(), &'static str> {
    info!(
        "Making API request to {}:{}{}",
        cfg.api_host, cfg.api_port, cfg.api_path
    );

    LED_COMMANDS.signal(LedCommand::SetStatus(StatusColor::Purple));

    // Retry a few times on network errors.
    for attempt in 1..=API_RETRY_COUNT {
        info!("HTTP attempt {}/{}", attempt, API_RETRY_COUNT);

        // Small buffers are enough for a tiny POST + short response status line.
        let mut rx_buf = [0u8; 512];
        let mut tx_buf = [0u8; 512];
        let mut socket = TcpSocket::new(stack, &mut rx_buf, &mut tx_buf);

        // Connect using the configured host and port.
        let endpoint = IpEndpoint::from((cfg.api_host, cfg.api_port));

        // Connect with a timeout.
        match embassy_time::with_timeout(
            Duration::from_secs(API_TIMEOUT_SECS),
            socket.connect(endpoint),
        )
        .await
        {
            Ok(Ok(())) => {
                debug!("TCP connected to API");
            }
            Ok(Err(_e)) => {
                warn!("TCP connect error");
                continue;
            }
            Err(_) => {
                warn!("TCP connect timeout");
                continue;
            }
        }

        // Build a minimal HTTP/1.1 POST request.
        let mut request: heapless::String<256> = heapless::String::new();
        write!(
            &mut request,
            "POST {} HTTP/1.1\r\nHost: {}\r\nContent-Length: 0\r\nConnection: close\r\n\r\n",
            cfg.api_path,
            cfg.api_host,
        )
        .map_err(|_| "format error")?;

        if let Err(_e) = embassy_time::with_timeout(
            Duration::from_secs(API_TIMEOUT_SECS),
            socket.write_all(request.as_bytes()),
        )
        .await
        {
            warn!("HTTP write failed");
            continue;
        }

        // Wait briefly for any response; we don't parse it yet.
        let mut tmp = [0u8; 64];
        let _ = embassy_time::with_timeout(
            Duration::from_secs(API_TIMEOUT_SECS),
            socket.read(&mut tmp),
        )
        .await;

        info!("API request complete");

        // Success – set status LED back to green and update a placeholder energy level.
        LED_COMMANDS.signal(LedCommand::SetStatus(StatusColor::Green));
        LED_COMMANDS.signal(LedCommand::SetEnergyMeter(5));
        return Ok(());
    }

    Err("all HTTP attempts failed")
}

// Note: StaticCell is needed for static allocation
use static_cell::StaticCell;
use embassy_executor::Spawner;
