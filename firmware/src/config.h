/**
 * Wall Clock In Machine - Configuration
 * 
 * Hardware configuration and constants
 */

#ifndef CONFIG_H
#define CONFIG_H

// Firmware version
#define FIRMWARE_VERSION "1.0.0"

// ===== HARDWARE PIN ASSIGNMENTS =====
#define PIN_BUTTON      9    // GPIO9 - Toggle switch input
#define PIN_LED_DATA    8    // GPIO8 - WS2812B LED strip data
#define PIN_BATTERY_ADC 4    // GPIO4 - Battery voltage sensing (ADC1_CH4)

// ===== LED CONFIGURATION =====
#define NUM_LEDS        8    // Total LEDs (1 status + 7 energy meter)
#define LED_TYPE        WS2812B
#define COLOR_ORDER     GRB
#define LED_BRIGHTNESS  128  // Default brightness (0-255)

// LED indices
#define LED_STATUS      0    // First LED is status indicator
#define LED_ENERGY_START 1   // Energy meter starts at LED 1
#define LED_ENERGY_COUNT 7   // 7 LEDs for energy meter

// ===== TIMING CONFIGURATION =====
#define BUTTON_DEBOUNCE_MS     50   // Button debounce time
#define BUTTON_LONG_PRESS_MS   3000 // Long press for config reset
#define API_TIMEOUT_MS         10000 // API call timeout
#define API_RETRY_COUNT        3     // Number of retries on failure
#define WIFI_CONNECT_TIMEOUT_S 30    // WiFi connection timeout
#define ENERGY_UPDATE_INTERVAL_MS 300000 // Update energy meter every 5 min

// ===== WORK CONFIGURATION =====
#define DEFAULT_WORK_HOURS  8    // Standard 8-hour workday
#define WORK_HOURS_SECONDS  (DEFAULT_WORK_HOURS * 3600)

// ===== POWER MANAGEMENT =====
#define BATTERY_VOLTAGE_FULL  4.2  // Fully charged LiPo
#define BATTERY_VOLTAGE_EMPTY 3.0  // Empty LiPo
#define BATTERY_ADC_RATIO     2.0  // Voltage divider ratio
#define DEEP_SLEEP_DURATION_S 3600 // Sleep 1 hour when idle

// ===== WIFI CONFIGURATION =====
#define WIFI_AP_SSID      "WallClockIn-Setup"
#define WIFI_AP_PASSWORD  ""  // Open network for setup
#define WIFI_PORTAL_TIMEOUT_S 180  // Config portal timeout

// ===== API CONFIGURATION =====
#define API_ENDPOINT_MAX_LEN  128
#define API_TOKEN_MAX_LEN     64
#define PROJECT_ID            "office-time"  // Default project name

// ===== LOGGING =====
#define LOG_LEVEL_ERROR   0
#define LOG_LEVEL_WARN    1
#define LOG_LEVEL_INFO    2
#define LOG_LEVEL_DEBUG   3

#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_INFO
#endif

// Logging macros
#if LOG_LEVEL >= LOG_LEVEL_ERROR
#define LOG_ERROR(msg, ...) Serial.printf("[ERROR] " msg "\n", ##__VA_ARGS__)
#else
#define LOG_ERROR(msg, ...)
#endif

#if LOG_LEVEL >= LOG_LEVEL_WARN
#define LOG_WARN(msg, ...) Serial.printf("[WARN] " msg "\n", ##__VA_ARGS__)
#else
#define LOG_WARN(msg, ...)
#endif

#if LOG_LEVEL >= LOG_LEVEL_INFO
#define LOG_INFO(msg, ...) Serial.printf("[INFO] " msg "\n", ##__VA_ARGS__)
#else
#define LOG_INFO(msg, ...)
#endif

#if LOG_LEVEL >= LOG_LEVEL_DEBUG
#define LOG_DEBUG(msg, ...) Serial.printf("[DEBUG] " msg "\n", ##__VA_ARGS__)
#else
#define LOG_DEBUG(msg, ...)
#endif

// ===== STORAGE KEYS (Preferences) =====
#define PREF_NAMESPACE      "wallclock"
#define PREF_API_ENDPOINT   "api_url"
#define PREF_API_TOKEN      "api_token"
#define PREF_WORK_HOURS     "work_hours"
#define PREF_LED_BRIGHTNESS "led_bright"
#define PREF_CURRENT_BEAT   "beat_id"
#define PREF_CLOCK_IN_TIME  "clock_in"

#endif // CONFIG_H
