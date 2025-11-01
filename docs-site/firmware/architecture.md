# Firmware Architecture

Overview of the async task-based architecture using Embassy.

## Async Task Architecture

The firmware uses Embassy's async executor to run concurrent tasks:

```
Embassy Executor
├── Button Task (tasks/button.rs)
│   ├── Async debouncing
│   ├── Long-press detection
│   └── Event signaling
├── LED Task (tasks/led.rs)
│   ├── WS2812B control via RMT
│   ├── Status indication
│   └── Energy meter display
└── WiFi Task (tasks/wifi.rs)
    ├── Network management
    ├── API communication
    └── State synchronization
```

## Task Communication

Tasks communicate via Embassy's `Signal` primitive:
- Button Task → WiFi Task (button events)
- WiFi Task → LED Task (status updates)
- Type-safe, lock-free message passing

## Modules
- **main.rs**: Embassy executor initialization
- **config.rs**: Hardware constants and configuration
- **tasks/button.rs**: Async button handling with debouncing
- **tasks/led.rs**: WS2812B LED control (status + energy meter)
- **tasks/wifi.rs**: WiFi connection and API integration

## Data Flow
- Main loop polls/debounces button → state change
- Timer (5 min) → api → backend sync
- NTP sync at boot for accurate timestamps

## Storage
- NVS (non-volatile storage) for WiFi and API settings
- Optional offline session cache (future)

## Error Handling
- Network: exponential backoff (1s, 5s, 15s)
- API 5xx: retry; 4xx: surface to user
- Brownout: reduce brightness; pause sync

## Extensibility
- Project selection via DIP or long-press menu
- Additional sensors can publish metrics via API

---

See: [Installation](installation.md), [Configuration](configuration.md), [API Integration](api-integration.md)