//! Configuration constants for the Wall Clock In Machine

pub const FIRMWARE_VERSION: &str = env!("CARGO_PKG_VERSION");

// Pin assignments (ESP32-C6 DevKitC-1)
pub const BUTTON_PIN: u8 = 9; // GPIO9 - Toggle switch input
pub const LED_PIN: u8 = 8; // GPIO8 - WS2812B LED strip data
pub const BATTERY_ADC_PIN: u8 = 4; // GPIO4 - Battery voltage sensing

// LED configuration
pub const NUM_LEDS: usize = 8; // 1 status + 7 energy
pub const LED_BRIGHTNESS: u8 = 128;

pub const LED_STATUS: usize = 0;
pub const LED_ENERGY_START: usize = 1;
pub const LED_ENERGY_COUNT: usize = 7;

// Timing configuration
pub const BUTTON_DEBOUNCE_MS: u64 = 50;
pub const BUTTON_LONG_PRESS_MS: u64 = 2000;

pub const API_TIMEOUT_SECS: u64 = 10;
pub const API_RETRY_COUNT: u8 = 3;

pub const WIFI_CONNECT_TIMEOUT_SECS: u64 = 30;
pub const ENERGY_UPDATE_INTERVAL_MS: u64 = 300_000; // 5 min

// Work configuration
pub const WORK_SESSION_HOURS: u8 = 8;

// Power management
pub const BATTERY_VOLTAGE_FULL: f32 = 4.2;
pub const BATTERY_VOLTAGE_EMPTY: f32 = 3.0;
pub const BATTERY_ADC_RATIO: f32 = 2.0; // Voltage divider ratio
pub const DEEP_SLEEP_MINUTES: u64 = 60;

// WiFi configuration defaults
pub const WIFI_AP_SSID: &str = "WallClockIn-Setup";
pub const WIFI_AP_PASSWORD: &str = ""; // Open

// ---------------------------------------------------------------------------
// Network & API configuration used by the Rust firmware today
// ---------------------------------------------------------------------------

/// Static network configuration used by the WiFi task.
///
/// There is currently **no web configuration portal** – the easiest way to point
/// the device at your own backend is to change these values and re-flash.
pub struct NetworkConfig {
    /// 2.4GHz WiFi SSID
    pub wifi_ssid: &'static str,
    /// WiFi password
    pub wifi_password: &'static str,
    /// API host name or IP (e.g. `192.168.1.50` or `api.local`)
    pub api_host: &'static str,
    /// API TCP port (e.g. 8000)
    pub api_port: u16,
    /// Path for the clock-toggle endpoint (e.g. `/api/timer/toggle`)
    pub api_path: &'static str,
}

/// Default network configuration.
///
/// **Edit this block** for your own setup.
pub const NETWORK_CONFIG: NetworkConfig = NetworkConfig {
    wifi_ssid: "YOUR_WIFI_SSID",
    wifi_password: "YOUR_WIFI_PASSWORD",
    api_host: "192.168.1.100",
    api_port: 8000,
    api_path: "/api/timer/toggle",
};
