# Wall Clock In Machine 🕐⚡

![Documentation](https://github.com/lanterno/office-wall-clock/actions/workflows/deploy-docs.yml/badge.svg)

A physical desk button that automatically tracks your work hours. No more typing curl commands!

## 📖 Documentation

**[Read the full documentation →](https://lanterno.github.io/office-wall-clock/)**

Complete guides for building, assembling, and using your Wall Clock In Machine.

## What Is This?

The Wall Clock In Machine is a smart IoT device that sits on your desk and makes time tracking effortless. Simply press the button when you arrive at work and press it again when you leave. The device automatically communicates with your timer API backend to log your work hours.

### Key Features

- **One-Touch Operation**: Single button toggles between "clocked in" and "clocked out"
- **Visual Status Indicator**: LED shows your current work status
- **Energy Meter**: Visual representation of remaining work hours (8-hour workday)
- **WiFi Connectivity**: Automatically syncs with your timer API
- **Battery Powered**: No cables cluttering your desk (10-14 days per charge)
- **Modern Firmware**: Built with Rust for safety, performance, and reliability

### Why Build This?

**The Problem**: Opening a terminal and typing curl commands 2x per day wastes time and interrupts workflow.

**The Solution**: Press a physical button → API call happens automatically → Get back to work!

**Time Saved**: ~2.6 hours per year + no context switching!

## Quick Links

### � Getting Started
- [Project Overview](https://lanterno.github.io/office-wall-clock/getting-started/overview/) - Is this project right for you?
- [Quick Start Guide](https://lanterno.github.io/office-wall-clock/getting-started/quick-start/) - Build in 2-3 hours

### 🔧 Hardware
- [Bill of Materials](https://lanterno.github.io/office-wall-clock/hardware/bill-of-materials/) - What to buy (~$35)
- [Hardware Specifications](https://lanterno.github.io/office-wall-clock/hardware/specifications/) - Technical details
- [Enclosure Design](https://lanterno.github.io/office-wall-clock/hardware/enclosure-design/) - Physical dimensions

### 💾 Firmware
- [Firmware Overview](https://lanterno.github.io/office-wall-clock/firmware/overview/) - Architecture and features
- [Installation Guide](https://lanterno.github.io/office-wall-clock/firmware/installation/) - Flash the device
- [Development](firmware/README.md) - Build from source

### 🔨 Assembly
- [Assembly Guide](https://lanterno.github.io/office-wall-clock/assembly/preparation/) - Step-by-step instructions
- [Testing](https://lanterno.github.io/office-wall-clock/assembly/testing/) - Verify it works

### 📚 Usage
- [Daily Operation](https://lanterno.github.io/office-wall-clock/usage/daily-operation/) - How to use it
- [LED Indicators](https://lanterno.github.io/office-wall-clock/usage/led-indicators/) - What the lights mean
- [Maintenance](https://lanterno.github.io/office-wall-clock/usage/maintenance/) - Keep it running

## Technical Stack

- **Microcontroller**: ESP32-C6 DevKitC-1 (RISC-V, WiFi, USB-C)
- **Programming Language**: Rust (pure Rust with esp-hal + Embassy)
- **Firmware Framework**: Embassy async runtime
- **LED Display**: WS2812B addressable RGB LEDs
- **Button**: Mechanical toggle switch
- **Power**: LiPo battery with USB-C charging
- **Backend API**: Your existing FastAPI timer service

## Design Philosophy

### Hardware
- **Minimal & Elegant**: Clean lines, professional appearance
- **Durable**: Built to last daily use for years
- **No Screen**: LEDs only - reduces complexity and power consumption
- **Tactile Feedback**: Physical button with satisfying click

### Software
- **Reliable**: Async Rust firmware with clear separation of button, LED, and WiFi tasks
- **Efficient**: Designed for low-power operation on ESP32-C6 (deep sleep planned)
- **Configurable**: WiFi + API set via `firmware/src/config.rs` (`NETWORK_CONFIG`)

## Time Savings Calculation

**Current process**: Open terminal, type curl command (~15 seconds × 2 times/day)  
**New process**: Press button (~2 seconds × 2 times/day)  
**Daily savings**: 26 seconds  
**Annual savings**: ~2.6 hours  
**Plus**: No context switching, no forgetting to log time!

## Technical Stack

- **Microcontroller**: ESP32-C6 DevKitC-1 (RISC-V, WiFi 6, USB-C, native Rust support)
- **Programming Language**: Rust with esp-hal 0.20 + Embassy 0.6 (pure Rust, no C!)
- **Networking**: `esp-wifi` + `embassy-net` (async TCP/IP)
- **LED Display**: WS2812B addressable RGB LEDs (`smart-leds`, `esp-hal-smartled`)
- **Button**: Mechanical SPDT toggle switch
- **Battery**: 3.7V 2000mAh LiPo with TP4056 USB-C charging
- **Total Cost**: ~$35 including enclosure

### Why Rust?
- **Safety**: Memory-safe with zero-cost abstractions
- **Performance**: 75% smaller binaries than C (~150KB)
- **Modern**: Async/await, strong type system, great tooling
- **Official Support**: Active esp-rs community and Espressif backing

## Repository Structure

```
wall-clock/
├── README.md           # Project overview (this file)
├── Makefile            # Build commands (rust-build, rust-flash, docs, etc.)
├── mkdocs.yml          # Documentation site configuration
├── docs-site/          # Documentation website source (MkDocs Material)
│   ├── getting-started/
│   ├── hardware/
│   ├── firmware/
│   ├── assembly/
│   └── usage/
├── firmware/           # Rust firmware source code
│   └── src/
│       ├── main.rs     # Embassy executor & task spawning
│       ├── config.rs   # Hardware + NETWORK_CONFIG (WiFi + API)
│       └── tasks/      # Async tasks (button, LED, WiFi + HTTP)
└── target/             # Build artifacts (ignored by git)
```

## Development

### Build Firmware

```fish
# Install Rust toolchain
rustup target add riscv32imc-unknown-none-elf
cargo install espflash --locked

# Build and flash
make rust-build
make rust-flash
```

See [firmware/README.md](firmware/README.md) for detailed development instructions.

### Documentation Site

```bash
# Install dependencies
pip install -r requirements-docs.txt

# Preview locally
mkdocs serve

# Deploy to GitHub Pages
git push origin main  # Auto-deploys via GitHub Actions
```

## Contributing

This is a personal project, but suggestions and improvements are welcome! Feel free to:
- Open issues for bugs or feature requests
- Submit pull requests with improvements
- Share your build photos and modifications

## License

See [LICENSE](LICENSE) file for details.

## Acknowledgments

Built with:
- [esp-rs](https://github.com/esp-rs) - Rust on ESP32
- [Embassy](https://embassy.dev/) - Async embedded framework
- [MkDocs Material](https://squidfunk.github.io/mkdocs-material/) - Documentation theme

---

**Ready to build?** Start with the [Quick Start Guide](https://lanterno.github.io/office-wall-clock/getting-started/quick-start/)!
