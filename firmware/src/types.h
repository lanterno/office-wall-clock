/**
 * Wall Clock In Machine - Common Type Definitions
 */

#ifndef TYPES_H
#define TYPES_H

#include <Arduino.h>

// Device states
enum class DeviceState {
  STARTUP,
  WIFI_CONNECTING,
  IDLE_CLOCKED_OUT,
  API_CALLING,
  WORKING_CLOCKED_IN,
  ERROR,
  CONFIG_MODE,
  DEEP_SLEEP
};

// Button events
enum class ButtonEvent {
  NONE,
  PRESSED,
  RELEASED,
  LONG_PRESS
};

// LED status colors
enum class StatusColor {
  RED,       // Clocked out
  GREEN,     // Clocked in / working
  BLUE,      // WiFi connecting
  YELLOW,    // API error
  PURPLE,    // Charging
  WHITE,     // Config mode
  OFF        // LED off
};

// API response structure
struct ApiResponse {
  bool success;
  int http_code;
  String beat_id;
  unsigned long timestamp;
  String error_message;
};

// Device configuration
struct DeviceConfig {
  char api_endpoint[128];
  char api_token[64];
  uint8_t work_hours;
  uint8_t led_brightness;
  bool enable_sleep;
  
  // Constructor with defaults
  DeviceConfig() {
    strcpy(api_endpoint, "");
    strcpy(api_token, "");
    work_hours = 8;
    led_brightness = 128;
    enable_sleep = true;
  }
};

// Work session data
struct WorkSession {
  String beat_id;
  unsigned long start_time;  // Unix timestamp
  bool is_active;
  
  WorkSession() {
    beat_id = "";
    start_time = 0;
    is_active = false;
  }
};

#endif // TYPES_H
