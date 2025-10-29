# Wall Clock In Machine 🕐⚡

**# Wall Clock In Machine

![Documentation](https://github.com/lanterno/beats/actions/workflows/deploy-docs.yml/badge.svg)

A physical desk button that automatically tracks your work hours. No more typing curl commands!

## 📖 Documentation

**[Read the full documentation →](https://lanterno.github.io/beats/)**

Complete guides for building, assembling, and using your Wall Clock In Machine.**

## Project Overview

The Wall Clock In Machine is a smart IoT device that sits on your desk and makes time tracking effortless. Simply press the button when you arrive at work and press it again when you leave. The device automatically communicates with your timer API backend to log your work hours.

### Features

- **One-Touch Operation**: Single button toggles between "clocked in" and "clocked out"
- **Visual Status Indicator**: LED shows your current work status
- **Energy Meter**: Visual representation of remaining work hours (8-hour workday)
- **WiFi Connectivity**: Automatically syncs with your timer API
- **Battery Powered**: No cables cluttering your desk
- **Sleek Design**: Minimal, professional appearance

## Project Status

🚧 **In Development** - Documentation-first approach

This project follows a documentation-first methodology. All designs, specifications, and guides are created before implementation to ensure a smooth build process.

## Repository Structure

```
wallClockInMachine/
├── README.md                          # This file
├── api/                               # Backend timer API service
├── hardware/
│   ├── README.md                      # Hardware overview
│   ├── BILL_OF_MATERIALS.md          # Complete parts list with links
│   ├── HARDWARE_SPECS.md             # Technical specifications
│   ├── ENCLOSURE_DESIGN.md           # Box design and dimensions
│   └── WIRING_DIAGRAM.md             # Circuit connections
├── firmware/
│   ├── README.md                      # Firmware overview
│   ├── src/
│   │   ├── main.cpp                   # Main firmware code
│   │   ├── config.h                   # Configuration constants
│   │   ├── wifi_manager.cpp/h         # WiFi connectivity
│   │   ├── api_client.cpp/h           # API communication
│   │   ├── led_controller.cpp/h       # LED control logic
│   │   └── button_handler.cpp/h       # Button debouncing & logic
│   └── test/
│       └── test_*.cpp                 # Unit tests
├── docs/
│   ├── ASSEMBLY_GUIDE.md             # Step-by-step assembly
│   ├── FIRMWARE_INSTALLATION.md      # How to flash the device
│   ├── CONFIGURATION.md              # WiFi and API setup
│   ├── USAGE_GUIDE.md                # Daily operation
│   ├── TROUBLESHOOTING.md            # Common issues & solutions
│   └── images/                        # Diagrams and photos
└── tools/
    └── simulator/                     # Desktop simulator for testing
```

## Quick Start Guide

### Prerequisites

- Basic soldering skills
- Computer with USB port
- Screwdriver set
- Wire strippers
- Multimeter (recommended)

### Build Process Overview

1. **Order Components** (~$30-40 total, 1-2 weeks delivery)
2. **Assemble Hardware** (~2-3 hours)
3. **Flash Firmware** (~30 minutes)
4. **Configure Device** (~15 minutes)
5. **Start Using** (2 seconds per day!)

### Detailed Guides

- 📋 [Bill of Materials](hardware/BILL_OF_MATERIALS.md) - What to buy
- 🔧 [Assembly Guide](docs/ASSEMBLY_GUIDE.md) - How to build it
- 💾 [Firmware Installation](docs/FIRMWARE_INSTALLATION.md) - Programming the device
- ⚙️ [Configuration](docs/CONFIGURATION.md) - Setup WiFi and API
- 📖 [Usage Guide](docs/USAGE_GUIDE.md) - Daily operation

## Technical Stack

- **Microcontroller**: ESP32-C3 (WiFi, low power, USB-C)
- **Programming Language**: C++ (Arduino framework)
- **LED Display**: NeoPixel LED strip (WS2812B)
- **Button**: Mechanical toggle switch with LED
- **Power**: LiPo battery with USB-C charging
- **Backend API**: Your existing FastAPI timer service

## Design Philosophy

### Hardware
- **Minimal & Elegant**: Clean lines, professional appearance
- **Durable**: Built to last daily use for years
- **No Screen**: LEDs only - reduces complexity and power consumption
- **Tactile Feedback**: Physical button with satisfying click

### Software
- **Reliable**: Handles network failures gracefully
- **Efficient**: Low power consumption for all-day battery life
- **Tested**: Comprehensive test coverage
- **Configurable**: Easy WiFi and API setup via web interface

## Time Savings Calculation

**Current process**: Open terminal, type curl command (~15 seconds × 2 times/day)  
**New process**: Press button (~2 seconds × 2 times/day)  
**Daily savings**: 26 seconds  
**Annual savings**: ~2.6 hours  
**Plus**: No context switching, no forgetting to log time!

## Contributing

This is a personal project, but feel free to fork and adapt to your needs!

## License

See [LICENSE](LICENSE) file for details.

## Acknowledgments

Built with ☕ by someone who's tired of typing curl commands.

---

**Ready to build?** Start with the [Hardware Specifications](hardware/HARDWARE_SPECS.md)!
