# Installation

Set up your development environment and flash the firmware.

## Prerequisites
- Arduino IDE or PlatformIO
- Board package: ESP32 by Espressif
- Libraries: FastLED, WiFiManager, ArduinoJson, HTTPClient

## Steps (Arduino IDE)
1. Install ESP32 boards in Boards Manager
2. Install required libraries
3. Connect ESP32-C3 via USB-C
4. Select board and port
5. Open the firmware sketch / project
6. Compile and Upload

## First Boot
- Device will enter WiFi setup mode (fast rainbow)
- Connect to AP: `WALL-CLOCK-SETUP`
- Configure WiFi and API URL (see Configuration)

## PlatformIO (Optional)
- Open project folder in VS Code
- Select env: esp32c3
- Click “Build” then “Upload”

## Troubleshooting
- Unknown serial port → try different USB cable or driver
- Compile error → verify library versions
- Boot loop → press reset; lower LED brightness

---

Next: [Configuration](configuration.md)