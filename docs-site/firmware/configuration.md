# Configuration

Configure WiFi, API endpoint, and basic device options in the Rust firmware.

## Where to configure things (today)

In the current Rust firmware there is **no configuration portal** yet. All settings live
in Rust code:

- File: `firmware/src/config.rs`
- Type: `NetworkConfig`
- Constant: `NETWORK_CONFIG`

```rust
pub struct NetworkConfig {
    pub wifi_ssid: &'static str,
    pub wifi_password: &'static str,
    pub api_host: &'static str,
    pub api_port: u16,
    pub api_path: &'static str,
}

pub const NETWORK_CONFIG: NetworkConfig = NetworkConfig {
    wifi_ssid: "YOUR_WIFI_SSID",
    wifi_password: "YOUR_WIFI_PASSWORD",
    api_host: "192.168.1.100",
    api_port: 8000,
    api_path: "/api/timer/toggle",
};
```

### Steps to configure WiFi + API

1. Open `firmware/src/config.rs` in your editor.
2. Find the `NETWORK_CONFIG` constant.
3. Set:
   - `wifi_ssid` to your 2.4GHz WiFi network name
   - `wifi_password` to your WiFi password
   - `api_host` to your backend host (IP or DNS)
   - `api_port` to the backend port (e.g. `8000` for local dev)
   - `api_path` to the path of your toggle endpoint (default: `/api/timer/toggle`)
4. Rebuild and flash the firmware.
5. Press the button – the device will issue a minimal HTTP `POST` to that endpoint.

!!! note
    The default firmware sends a **simple POST request with no JSON body** and treats
    any successful TCP exchange as a “toggle”. See [API Integration](api-integration.md)
    for how to adapt this to your own API.

## Device Options

Other basic options are also in `firmware/src/config.rs`:

- `LED_BRIGHTNESS` – overall LED brightness (0–255)
- `WORK_SESSION_HOURS` – hours represented by a full energy meter
- `BUTTON_DEBOUNCE_MS` / `BUTTON_LONG_PRESS_MS` – button behavior

More advanced options like deep sleep, NTP, and on-device configuration are
**planned** but not implemented yet in the Rust firmware.

---

See: [API Integration](api-integration.md), [Daily Operation](../usage/daily-operation.md)