# Wall Clock In Machine – Rust Firmware (ESP32-C6 DevKitC-1)

Modern Rust firmware using **state-of-the-art embedded tools**:
- **esp-hal 0.20**: Pure Rust hardware abstraction (no C!)
- **Embassy 0.6**: Modern async/await runtime for embedded
- **defmt**: Zero-cost structured logging
- **Stable Rust**: No nightly toolchain required

## Why This Stack?

### Pure Rust (no C)
- ✅ Complete type safety & better compile-time guarantees
- ✅ 75% smaller binaries (~150KB vs ~600KB)
- ✅ 3-4x faster compilation
- ✅ Single language throughout

### Embassy Async
- ✅ Modern concurrency patterns (async/await)
- ✅ Non-blocking I/O & better power efficiency
- ✅ Industry-standard framework

### Performance
- **Binary Size**: ~150KB
- **Build Time**: 30-60s
- **RAM Usage**: ~50KB
- **Boot Time**: ~500ms

## Prerequisites

```fish
# Install Rust (if needed)
curl -fsSL https://sh.rustup.rs | sh

# Add RISC-V embedded target (no_std for ESP32-C6)
rustup target add riscv32imc-unknown-none-elf

# Install espflash
cargo install espflash --locked
```

## Project Structure

```
firmware/
├── Cargo.toml              # Modern dependencies (esp-hal, Embassy)
├── rust-toolchain.toml     # Stable Rust
├── .cargo/config.toml      # Build configuration
└── src/
    ├── main.rs             # Embassy executor & initialization
    ├── config.rs           # Hardware + NETWORK_CONFIG
    └── tasks/              # Async task modules
        ├── mod.rs          # Task exports
        ├── button.rs       # Button handling (async)
        ├── led.rs          # WS2812B LED controller (async)
        └── wifi.rs         # WiFi + API client (async)
```

## Build & Flash

```fish
# From repository root (recommended)
make rust-build        # Build firmware
make rust-flash        # Flash to device & monitor
make rust-monitor      # Serial console only

# Or from firmware/ directory
cd firmware
cargo build --release
cargo run --release
```

## Quick Commands

```fish
make rust-build        # Build firmware (release)
make rust-build-dev    # Build debug (faster)
make rust-flash        # Flash & monitor
make rust-monitor      # Serial console
make rust-clippy       # Lint code
make rust-fmt          # Format code
make rust-size         # Check binary size
make rust-clean        # Clean build artifacts
```

## Architecture

Task-based async architecture with Embassy executor:

```
┌─────────────────────────────────────────┐
│         Embassy Executor                │
│         (Async Runtime)                 │
├─────────────────────────────────────────┤
│  Button Task  │  LED Task  │  WiFi Task │
│  • Debounce   │  • WS2812B │  • Network │
│  • Events     │  • Effects │  • API     │
└─────────────────────────────────────────┘
```

Tasks communicate via Embassy's `Signal` - type-safe, lock-free messaging.

## Configuration

Hardware configuration and network settings live in `src/config.rs`:

```rust
pub const BUTTON_PIN: u8 = 9;  // GPIO9 - Button input
pub const LED_PIN: u8 = 8;     // GPIO8 - WS2812B data
pub const NUM_LEDS: usize = 8; // 1 status + 7 energy meter
pub const LED_BRIGHTNESS: u8 = 128; // 0-255

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

Edit `NETWORK_CONFIG` to point the firmware at your WiFi + backend, then rebuild
and flash.

## Features

**Implemented:**
- ✅ Async button handling (debounce, long-press detection)
- ✅ WS2812B LED control via RMT (status + energy meter)
- ✅ WiFi connection (async, pure Rust)
- ✅ Embassy async runtime
- ✅ defmt logging
 - ✅ Minimal HTTP POST client using `embassy-net` `TcpSocket`

**Planned:**
- ⏳ Rich API integration (JSON payloads, TLS, retries with status codes)
- ⏳ NVS configuration storage + web portal
- ⏳ Deep sleep + power management
- ⏳ OTA firmware updates

## Troubleshooting

- If flashing fails, ensure the device is connected and not claimed by another serial monitor.
- On macOS, if you see permission issues, try unplug/replug the device or a different USB‑C cable.
- If build fails with target issues, re-run: `rustup target add riscv32imc-unknown-none-elf`.
- **Build errors?** Try: `rustup update stable && cargo clean`
- **Flash fails?** Check USB connection, try different cable, or press BOOT button while connecting
- **WiFi won't connect?** Verify 2.4GHz network (not 5GHz), check SSID/password spelling

## Resources

- **Documentation**: https://docs.esp-rs.org/ - Official esp-rs docs
- **Embassy Guide**: https://embassy.dev/ - Async framework
- **Community**: #esp-rs:matrix.org - Get help
- **Examples**: https://github.com/esp-rs/esp-hal/tree/main/examples

## Learning Path

1. **Start**: Read esp-hal examples for ESP32-C6
2. **Learn**: Embassy async patterns
3. **Practice**: Build this project!
4. **Master**: Contribute back to community

## Development notes

- Build only: `make rust-build`
- Flash + monitor: `make rust-flash` (or `cargo run --release` from `firmware/`)
- Monitor only: `make rust-monitor` (or `espflash monitor`)
