/**
 * Wall Clock In Machine - Main Program
 * 
 * A desk device that tracks office time with one button press
 */

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiManager.h>
#include <Preferences.h>
#include "config.h"
#include "types.h"
#include "button_handler.h"
#include "led_controller.h"
#include "api_client.h"

// Global objects
ButtonHandler button(PIN_BUTTON);
LEDController leds;
ApiClient api;
Preferences prefs;
WiFiManager wifiManager;

// State variables
DeviceState currentState = DeviceState::STARTUP;
WorkSession session;
DeviceConfig config;
unsigned long last_energy_update = 0;
bool config_portal_running = false;

// Function declarations
void setup();
void loop();
void loadConfiguration();
void saveConfiguration();
void startConfigPortal();
void handleButtonPress();
void handleClock InRequest();
void handleClockOutRequest();
void updateEnergyMeter();
void enterDeepSleep();
float getBatteryVoltage();
uint8_t getBatteryPercent();

void setup() {
  Serial.begin(115200);
  delay(1000);  // Wait for serial to initialize
  
  LOG_INFO("=================================");
  LOG_INFO("Wall Clock In Machine v%s", FIRMWARE_VERSION);
  LOG_INFO("=================================");
  
  // Initialize hardware
  button.begin();
  leds.begin();
  
  // Show startup animation
  leds.setStatus(StatusColor::BLUE);
  delay(500);
  
  // Load saved configuration
  prefs.begin(PREF_NAMESPACE, false);
  loadConfiguration();
  
  // Check for config reset (long press during boot)
  LOG_INFO("Press button to enter config mode...");
  unsigned long start_time = millis();
  while (millis() - start_time < 3000) {
    ButtonEvent event = button.update();
    if (event == ButtonEvent::LONG_PRESS) {
      LOG_INFO("Config mode requested");
      startConfigPortal();
      return;
    }
    delay(10);
  }
  
  // Connect to WiFi
  LOG_INFO("Connecting to WiFi...");
  currentState = DeviceState::WIFI_CONNECTING;
  leds.setStatus(StatusColor::BLUE);
  
  // Set custom WiFi Manager parameters
  WiFiManagerParameter custom_api_endpoint("api", "API Endpoint", config.api_endpoint, 128);
  WiFiManagerParameter custom_api_token("token", "API Token", config.api_token, 64);
  
  wifiManager.addParameter(&custom_api_endpoint);
  wifiManager.addParameter(&custom_api_token);
  wifiManager.setConfigPortalTimeout(WIFI_PORTAL_TIMEOUT_S);
  
  // Try to connect
  if (!wifiManager.autoConnect(WIFI_AP_SSID, WIFI_AP_PASSWORD)) {
    LOG_ERROR("Failed to connect to WiFi");
    currentState = DeviceState::ERROR;
    leds.setStatus(StatusColor::YELLOW);
    delay(3000);
    ESP.restart();
  }
  
  // Save any new parameters from config portal
  if (strlen(custom_api_endpoint.getValue()) > 0) {
    strcpy(config.api_endpoint, custom_api_endpoint.getValue());
    strcpy(config.api_token, custom_api_token.getValue());
    saveConfiguration();
  }
  
  LOG_INFO("WiFi connected!");
  LOG_INFO("IP address: %s", WiFi.localIP().toString().c_str());
  
  // Initialize API client
  api.begin(config.api_endpoint, config.api_token);
  
  // Check if we have an active session from previous boot
  String saved_beat_id = prefs.getString(PREF_CURRENT_BEAT, "");
  if (saved_beat_id.length() > 0) {
    LOG_INFO("Found active session: %s", saved_beat_id.c_str());
    session.beat_id = saved_beat_id;
    session.start_time = prefs.getULong(PREF_CLOCK_IN_TIME, 0);
    session.is_active = true;
    currentState = DeviceState::WORKING_CLOCKED_IN;
    leds.setStatus(StatusColor::GREEN);
  } else {
    currentState = DeviceState::IDLE_CLOCKED_OUT;
    leds.setStatus(StatusColor::RED);
  }
  
  LOG_INFO("System ready!");
  LOG_INFO("Battery: %d%% (%.2fV)", getBatteryPercent(), getBatteryVoltage());
}

void loop() {
  // Update button state
  ButtonEvent event = button.update();
  
  // Handle button events
  if (event == ButtonEvent::PRESSED) {
    handleButtonPress();
  } else if (event == ButtonEvent::LONG_PRESS) {
    LOG_INFO("Long press detected - entering config mode");
    startConfigPortal();
  }
  
  // Update energy meter periodically if working
  if (currentState == DeviceState::WORKING_CLOCKED_IN) {
    if (millis() - last_energy_update > ENERGY_UPDATE_INTERVAL_MS) {
      updateEnergyMeter();
      last_energy_update = millis();
    }
  }
  
  // Handle animations
  if (currentState == DeviceState::WIFI_CONNECTING) {
    leds.pulseStatus(StatusColor::BLUE);
  }
  
  // Check battery level
  uint8_t battery_pct = getBatteryPercent();
  if (battery_pct < 10) {
    LOG_WARN("Low battery: %d%%", battery_pct);
  }
  
  // Small delay to prevent tight loop
  delay(10);
}

void loadConfiguration() {
  strcpy(config.api_endpoint, prefs.getString(PREF_API_ENDPOINT, "").c_str());
  strcpy(config.api_token, prefs.getString(PREF_API_TOKEN, "").c_str());
  config.work_hours = prefs.getUChar(PREF_WORK_HOURS, DEFAULT_WORK_HOURS);
  config.led_brightness = prefs.getUChar(PREF_LED_BRIGHTNESS, LED_BRIGHTNESS);
  
  leds.setBrightness(config.led_brightness);
  
  LOG_INFO("Configuration loaded");
  LOG_DEBUG("API Endpoint: %s", config.api_endpoint);
  LOG_DEBUG("Work hours: %d", config.work_hours);
}

void saveConfiguration() {
  prefs.putString(PREF_API_ENDPOINT, config.api_endpoint);
  prefs.putString(PREF_API_TOKEN, config.api_token);
  prefs.putUChar(PREF_WORK_HOURS, config.work_hours);
  prefs.putUChar(PREF_LED_BRIGHTNESS, config.led_brightness);
  
  LOG_INFO("Configuration saved");
}

void startConfigPortal() {
  LOG_INFO("Starting configuration portal...");
  currentState = DeviceState::CONFIG_MODE;
  leds.setStatus(StatusColor::WHITE);
  
  WiFiManagerParameter custom_api_endpoint("api", "API Endpoint", config.api_endpoint, 128);
  WiFiManagerParameter custom_api_token("token", "API Token (optional)", config.api_token, 64);
  
  wifiManager.addParameter(&custom_api_endpoint);
  wifiManager.addParameter(&custom_api_token);
  
  if (!wifiManager.startConfigPortal(WIFI_AP_SSID, WIFI_AP_PASSWORD)) {
    LOG_ERROR("Config portal failed");
  } else {
    // Save new configuration
    strcpy(config.api_endpoint, custom_api_endpoint.getValue());
    strcpy(config.api_token, custom_api_token.getValue());
    saveConfiguration();
    LOG_INFO("Configuration updated, restarting...");
  }
  
  ESP.restart();
}

void handleButtonPress() {
  LOG_INFO("Button pressed - current state: %d", (int)currentState);
  
  if (currentState == DeviceState::IDLE_CLOCKED_OUT) {
    handleClockInRequest();
  } else if (currentState == DeviceState::WORKING_CLOCKED_IN) {
    handleClockOutRequest();
  }
}

void handleClockInRequest() {
  LOG_INFO("Clock in requested");
  currentState = DeviceState::API_CALLING;
  leds.pulseStatus(StatusColor::BLUE);
  
  ApiResponse response = api.clockIn(PROJECT_ID);
  
  if (response.success) {
    LOG_INFO("Clocked in successfully! Beat ID: %s", response.beat_id.c_str());
    
    session.beat_id = response.beat_id;
    session.start_time = millis() / 1000;  // Convert to seconds
    session.is_active = true;
    
    // Save session
    prefs.putString(PREF_CURRENT_BEAT, session.beat_id);
    prefs.putULong(PREF_CLOCK_IN_TIME, session.start_time);
    
    currentState = DeviceState::WORKING_CLOCKED_IN;
    leds.setStatus(StatusColor::GREEN);
    updateEnergyMeter();
    last_energy_update = millis();
  } else {
    LOG_ERROR("Clock in failed: %s", response.error_message.c_str());
    currentState = DeviceState::ERROR;
    leds.setStatus(StatusColor::YELLOW);
    delay(2000);
    currentState = DeviceState::IDLE_CLOCKED_OUT;
    leds.setStatus(StatusColor::RED);
  }
}

void handleClockOutRequest() {
  LOG_INFO("Clock out requested");
  currentState = DeviceState::API_CALLING;
  leds.pulseStatus(StatusColor::BLUE);
  
  ApiResponse response = api.clockOut(session.beat_id.c_str());
  
  if (response.success) {
    LOG_INFO("Clocked out successfully!");
    
    // Calculate work duration
    unsigned long duration = (millis() / 1000) - session.start_time;
    LOG_INFO("Work duration: %lu seconds (%.1f hours)", duration, duration / 3600.0);
    
    // Check if we completed the full workday
    if (duration >= (config.work_hours * 3600 * 0.95)) {  // 95% threshold
      LOG_INFO("Workday complete! 🎉");
      leds.rainbowCelebration();
      delay(3000);
    }
    
    // Clear session
    session.beat_id = "";
    session.start_time = 0;
    session.is_active = false;
    
    prefs.remove(PREF_CURRENT_BEAT);
    prefs.remove(PREF_CLOCK_IN_TIME);
    
    currentState = DeviceState::IDLE_CLOCKED_OUT;
    leds.setStatus(StatusColor::RED);
  } else {
    LOG_ERROR("Clock out failed: %s", response.error_message.c_str());
    currentState = DeviceState::ERROR;
    leds.setStatus(StatusColor::YELLOW);
    delay(2000);
    // Stay in working state on error
    currentState = DeviceState::WORKING_CLOCKED_IN;
    leds.setStatus(StatusColor::GREEN);
  }
}

void updateEnergyMeter() {
  if (!session.is_active) return;
  
  unsigned long elapsed_seconds = (millis() / 1000) - session.start_time;
  unsigned long work_seconds = config.work_hours * 3600;
  
  // Calculate remaining hours
  uint8_t hours_remaining = 0;
  if (elapsed_seconds < work_seconds) {
    hours_remaining = (work_seconds - elapsed_seconds + 3599) / 3600;  // Round up
  }
  
  LOG_DEBUG("Energy meter update: %d/%d hours remaining", hours_remaining, config.work_hours);
  leds.setEnergyMeter(hours_remaining, config.work_hours);
}

void enterDeepSleep() {
  LOG_INFO("Entering deep sleep...");
  leds.clear();
  
  // Configure wake-up on button press
  esp_sleep_enable_ext0_wakeup(PIN_BUTTON, LOW);
  
  esp_deep_sleep_start();
}

float getBatteryVoltage() {
  // Read ADC value (12-bit, 0-4095)
  int raw = analogRead(PIN_BATTERY_ADC);
  
  // Convert to voltage (considering voltage divider)
  float voltage = (raw / 4095.0) * 3.3 * BATTERY_ADC_RATIO;
  
  return voltage;
}

uint8_t getBatteryPercent() {
  float voltage = getBatteryVoltage();
  
  // Linear mapping from 3.0V (0%) to 4.2V (100%)
  float percent = (voltage - BATTERY_VOLTAGE_EMPTY) / 
                  (BATTERY_VOLTAGE_FULL - BATTERY_VOLTAGE_EMPTY) * 100.0;
  
  return constrain((int)percent, 0, 100);
}
