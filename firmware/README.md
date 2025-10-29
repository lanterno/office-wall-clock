# Firmware for Wall Clock In Machine

## Overview

This firmware runs on the ESP32-C3 microcontroller and provides all the logic for the Wall Clock In Machine device.

## Features

- ✅ WiFi connectivity with auto-reconnect
- ✅ Integration with Timer API backend
- ✅ Button handling with debouncing
- ✅ LED status and energy meter display
- ✅ Deep sleep for power saving
- ✅ Web-based configuration portal
- ✅ OTA (Over-The-Air) firmware updates
- ✅ Battery level monitoring

## Architecture

```
┌─────────────────────────────────────────────┐
│              Main Program                    │
│         (state machine logic)                │
└───┬─────────┬─────────┬─────────┬──────────┘
    │         │         │         │
    ▼         ▼         ▼         ▼
┌────────┬────────┬─────────┬──────────┐
│Button  │ LED    │ WiFi    │  API     │
│Handler │Control │Manager  │ Client   │
└────────┴────────┴─────────┴──────────┘
```

## File Structure

```
firmware/
├── platformio.ini              # PlatformIO project config
├── README.md                   # This file
├── src/
│   ├── main.cpp               # Main program entry
│   ├── config.h               # Configuration constants
│   ├── types.h                # Common type definitions
│   ├── button_handler.h/cpp   # Button debouncing & events
│   ├── led_controller.h/cpp   # LED animations & display
│   ├── wifi_manager.h/cpp     # WiFi connectivity
│   ├── api_client.h/cpp       # HTTP API communication
│   └── power_manager.h/cpp    # Battery & sleep management
├── test/
│   ├── test_button.cpp        # Button handler tests
│   ├── test_led.cpp           # LED controller tests
│   └── test_api.cpp           # API client tests
└── lib/
    └── (external libraries)
```

## Dependencies

All dependencies are managed via PlatformIO:

- **FastLED** (3.6.0): LED control
- **WiFiManager** (2.0.16): WiFi configuration portal
- **ArduinoJson** (6.21.3): JSON parsing
- **HTTPClient**: HTTP requests (built-in)
- **Preferences**: Non-volatile storage (built-in)

## Building

### Using PlatformIO (Recommended)

```bash
# Install PlatformIO
pip install platformio

# Navigate to firmware directory
cd firmware/

# Build firmware
pio run

# Upload to device
pio run --target upload

# Open serial monitor
pio device monitor
```

### Using Arduino IDE

1. Install ESP32 board support: https://docs.espressif.com/projects/arduino-esp32/
2. Install libraries via Library Manager:
   - FastLED
   - WiFiManager
   - ArduinoJson
3. Open `src/main.cpp`
4. Select Board: "ESP32C3 Dev Module"
5. Upload

## Configuration

### First-Time Setup

1. Power on device
2. Device creates WiFi hotspot: "WallClockIn-Setup"
3. Connect to hotspot with phone/laptop
4. Browser opens automatically (or go to 192.168.4.1)
5. Enter your WiFi credentials and API endpoint
6. Save - device reboots and connects

### Configuration Parameters

Stored in non-volatile memory:

```cpp
struct Config {
    char wifi_ssid[32];
    char wifi_password[64];
    char api_endpoint[128];      // e.g., "https://api.example.com"
    char api_token[64];          // Optional: Bearer token
    uint8_t work_hours;          // Default: 8
    uint8_t led_brightness;      // 0-255, default: 128
    bool enable_sleep;           // Default: true
};
```

### Resetting Configuration

Hold button during power-on for 5 seconds → factory reset

## Pin Assignments

```cpp
#define PIN_BUTTON      GPIO_NUM_9   // Toggle switch input
#define PIN_LED_DATA    GPIO_NUM_8   // WS2812B data line
#define PIN_BATTERY_ADC GPIO_NUM_4   // Battery voltage sense
#define NUM_LEDS        8            // Total LED count
```

## State Machine

```
┌─────────────┐
│   STARTUP   │──────┐
└─────────────┘      │
                     ▼
┌─────────────────────────────┐
│   WIFI_CONNECTING           │
└──────┬──────────────────────┘
       │ Connected
       ▼
┌─────────────────────────────┐
│   IDLE (Clocked Out)        │◄──────┐
│   Status LED: Red           │       │
└──────┬──────────────────────┘       │
       │ Button Press                 │
       ▼                              │
┌─────────────────────────────┐       │
│   API_CALL (Clock In)       │       │
└──────┬──────────────────────┘       │
       │ Success                      │
       ▼                              │
┌─────────────────────────────┐       │
│   WORKING (Clocked In)      │       │
│   Status LED: Green         │       │
│   Energy Meter: Counting    │       │
└──────┬──────────────────────┘       │
       │ Button Press                 │
       ▼                              │
┌─────────────────────────────┐       │
│   API_CALL (Clock Out)      │       │
└──────┬──────────────────────┘       │
       │ Success                      │
       └──────────────────────────────┘
```

## LED Patterns

### Status LED (LED #0)

| Color | Meaning | Pattern |
|-------|---------|---------|
| 🔴 Red | Clocked Out | Solid |
| 🟢 Green | Clocked In | Solid |
| 🔵 Blue | WiFi Connecting | Pulsing |
| 🟡 Yellow | API Error | Blinking Fast |
| 🟣 Purple | Charging | Breathing |
| ⚪ White | Configuration Mode | Blinking Slow |

### Energy Meter (LEDs #1-7)

Shows remaining work hours out of 8:

```
Hours Left │ LEDs Lit │ Color
───────────┼──────────┼───────────
   8-7     │  7 LEDs  │ 🟢 Green
   6-5     │  5-6     │ 🟢 Green
   4-3     │  3-4     │ 🟡 Yellow
   2-1     │  1-2     │ 🔴 Red
   0       │  0       │ 🎉 Rainbow!
```

## Power Management

### Sleep Modes

**Deep Sleep**: When idle and clocked out
- Current: 5µA
- Wake: Button press (GPIO interrupt)
- Duration: Indefinite

**Light Sleep**: When clocked in
- Current: ~2mA
- Wake: Every 5 minutes to update LEDs
- Purpose: Update energy meter

**Active**: During API calls and LED updates
- Current: ~100mA
- Duration: 5-10 seconds

### Battery Monitoring

```cpp
float getBatteryVoltage() {
    // Read ADC (12-bit, 0-3.3V with voltage divider)
    int raw = analogRead(PIN_BATTERY_ADC);
    return (raw / 4095.0) * 3.3 * 2.0;  // 2:1 divider
}

uint8_t getBatteryPercent() {
    float voltage = getBatteryVoltage();
    // 4.2V = 100%, 3.0V = 0%
    return constrain((voltage - 3.0) / 1.2 * 100, 0, 100);
}
```

## API Integration

### Endpoints

The firmware expects your Timer API to support:

**Clock In**:
```http
POST /api/timer/start
Content-Type: application/json
Authorization: Bearer {token}

{
  "project_id": "office-time"
}

Response: 200 OK
{
  "beat_id": "12345",
  "started_at": "2025-10-29T08:00:00Z"
}
```

**Clock Out**:
```http
POST /api/timer/stop
Content-Type: application/json
Authorization: Bearer {token}

{
  "beat_id": "12345"
}

Response: 200 OK
{
  "beat_id": "12345",
  "stopped_at": "2025-10-29T17:00:00Z",
  "duration": 28800
}
```

**Get Status** (optional, for recovery):
```http
GET /api/timer/current
Authorization: Bearer {token}

Response: 200 OK
{
  "is_running": true,
  "beat_id": "12345",
  "started_at": "2025-10-29T08:00:00Z",
  "elapsed": 14400
}
```

### Error Handling

- **Network Error**: Retry 3 times with exponential backoff
- **API Error**: Show yellow LED, keep local state
- **Timeout**: 10 second timeout per request
- **Recovery**: On boot, check current status from API

## Debugging

### Serial Output

Firmware outputs debug info at 115200 baud:

```
[INFO] Wall Clock In Machine v1.0.0
[INFO] Connecting to WiFi: MyNetwork
[INFO] WiFi connected, IP: 192.168.1.42
[INFO] Button pressed: Clock In
[API] POST /api/timer/start
[API] Response: 200 OK
[INFO] Now working, energy meter started
```

### Log Levels

```cpp
#define LOG_LEVEL_ERROR   0
#define LOG_LEVEL_WARN    1
#define LOG_LEVEL_INFO    2
#define LOG_LEVEL_DEBUG   3

// Set in config.h
#define LOG_LEVEL LOG_LEVEL_INFO
```

### Test Modes

Hold button + reset for test modes:

- **LED Test**: Cycle through all LED colors
- **WiFi Test**: Connect and show IP on serial
- **API Test**: Send test request
- **Battery Test**: Show voltage and percent

## Firmware Updates

### OTA Updates (Wireless)

When new firmware is available:

```bash
# Build firmware
pio run

# Upload via OTA (device must be on same network)
pio run --target upload --upload-port wall-clock-in.local
```

### USB Updates

```bash
# Connect device via USB-C
pio run --target upload
```

### Version Checking

Firmware periodically checks for updates:

```http
GET /api/firmware/version
Response: { "version": "1.0.1", "url": "https://..." }
```

If newer version available, download and flash automatically.

## Development

### Adding New Features

1. Create feature branch: `git checkout -b feature/my-feature`
2. Implement in appropriate module
3. Write unit tests in `test/`
4. Test on hardware
5. Update documentation
6. Submit PR

### Code Style

Follow Arduino/ESP32 conventions:
- Functions: camelCase
- Classes: PascalCase
- Constants: UPPER_SNAKE_CASE
- Variables: snake_case
- Indentation: 2 spaces

### Testing

Run unit tests:

```bash
pio test
```

Run on hardware:

```bash
pio test --environment native
```

## Troubleshooting

See [TROUBLESHOOTING.md](../docs/TROUBLESHOOTING.md) for common issues.

## License

See [LICENSE](../LICENSE) file.

---

**Ready to flash?** See [FIRMWARE_INSTALLATION.md](../docs/FIRMWARE_INSTALLATION.md)
