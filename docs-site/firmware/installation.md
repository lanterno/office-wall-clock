# Installation

Set up your development environment and flash the firmware.

## Prerequisites
- Rust toolchain via rustup (stable)
- Target: `riscv32imc-unknown-none-elf` (no_std embedded)
- `espflash` CLI for flashing and serial monitor

## Steps
1. Install Rust toolchain:
	```fish
	curl -fsSL https://sh.rustup.rs | sh
	```
2. Add ESP32-C3 target (no_std):
	```fish
	rustup target add riscv32imc-unknown-none-elf
	```
3. Install espflash:
	```fish
	cargo install espflash --locked
	```
4. Connect ESP32-C3 via USB-C
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
- Device will enter WiFi setup mode (coming soon in Rust)
- Connect to AP: `WALL-CLOCK-SETUP` (planned)
- Configure WiFi and API URL (see Configuration)

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