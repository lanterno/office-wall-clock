# Installation

Set up your development environment and flash the firmware.

## Prerequisites
- Rust toolchain via rustup (stable)
- Target: `riscv32imc-unknown-none-elf` (RISC-V no_std embedded for ESP32-C6)
- `espflash` CLI for flashing and serial monitor

## Steps
1. Install Rust toolchain:
	```fish
	curl -fsSL https://sh.rustup.rs | sh
	```
2. Add RISC-V embedded target (no_std):
	```fish
	rustup target add riscv32imc-unknown-none-elf
	```
3. Install espflash:
	```fish
	cargo install espflash --locked
	```
4. Connect ESP32-C6 DevKitC-1 via USB-C
5. Build and flash firmware:
	```fish
	cd firmware
	cargo build --release
	cargo run --release
	# Or use make commands:
	make rust-build
	make rust-flash
	```

## First Boot
- The device will try to connect to the WiFi network defined in `firmware/src/config.rs` (`NETWORK_CONFIG.wifi_ssid` / `wifi_password`).
- On success, the top LED turns **green** after boot and the device is ready to send API requests on button press.
- On failure, the top LED stays **blue/yellow** – double‑check your WiFi credentials in `config.rs` and re‑flash.

!!! note
    There is **no web-based configuration portal yet** in the Rust firmware. All WiFi and API settings are compile-time values in `firmware/src/config.rs`. See [Configuration](configuration.md) for details.

## Rust Workflow (Recommended)
- Open project folder in VS Code
- Edit Rust source files in `firmware/src/`
- Build and flash using the commands above

## Troubleshooting
- Unknown serial port → try different USB cable or driver
- Compile error → check Rust toolchain and target
- Boot loop → press reset; lower LED brightness

---

Next: [Configuration](configuration.md)