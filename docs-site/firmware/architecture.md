# Firmware Architecture

Overview of the state machine, modules, and data flow.

## State Machine
```
STARTUP → WIFI_CONNECTING → IDLE_CLOCKED_OUT ↔ WORKING_CLOCKED_IN → ERROR
```
- STARTUP: Hardware init, config load
- WIFI_CONNECTING: Connect or open captive portal
- IDLE_CLOCKED_OUT: Waiting for button down
- WORKING_CLOCKED_IN: Session running, periodic sync
- ERROR: Recoverable faults with retry/backoff

## Modules
- button_handler: Debounce, click/long-press
- led_controller: Status + energy meter animations
- api_client: HTTPS requests, retries, offline cache
- power_manager: Sleep/wake, low-battery handling
- config: Persistent settings (WiFi, API URL, brightness)

## Data Flow
- GPIO interrupt → button_handler → state change
- timer (5 min) → api_client → backend sync
- NTP sync at boot for accurate timestamps

## Storage
- Preferences (NVS) for settings
- EEPROM/FS for offline session cache (up to 50 entries)

## Error Handling
- Network: exponential backoff (1s, 5s, 15s)
- API 5xx: retry; 4xx: surface to user
- Brownout: reduce brightness; pause sync

## Extensibility
- Project selection via DIP or long-press menu
- Additional sensors can publish metrics via API

---

See: [Installation](installation.md), [Configuration](configuration.md), [API Integration](api-integration.md)