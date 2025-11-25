---
hide:
  - navigation
  - toc
---

# Wall Clock In Machine

<div class="hero-image" markdown>
  <h1>⚡ Automatic Time Tracking Device</h1>
  <p class="hero-subtitle">A physical desk device that tracks your office time with a single button press</p>
</div>

<div class="grid cards" markdown>

-   :material-clock-fast:{ .lg .middle } __2 Seconds Per Day__

    ---

    Press button when you arrive. Press when you leave. That's it!
    
    Save **2.6 hours per year** + eliminate context switching.

-   :material-cash-multiple:{ .lg .middle } __Under $35__

    ---

    Complete bill of materials with shopping links.
    
    All components available on Amazon or AliExpress.

-   :material-battery:{ .lg .middle } __10-14 Days Battery__

    ---

    Charge once every two weeks via USB-C.
    
    Deep sleep mode when idle saves power.

-   :material-wifi:{ .lg .middle } __WiFi Connected__

    ---

    Automatically syncs with your timer API.
    
    Works with any HTTP/HTTPS backend.

-   :material-led-on:{ .lg .middle } __Visual Feedback__

    ---

    Status LED shows current state.
    
    Energy meter shows hours remaining (like a thermal meter! 🌡️)

-   :material-open-source-initiative:{ .lg .middle } __100% Open Source__

    ---

    Complete schematics, firmware, and documentation.
    
    Modify and customize as you like!

</div>

---

## The Problem

Every day when you go to the office, you have to:

1. Open your terminal
2. Type a curl command to start your timer
3. Do the same when you leave

This takes **15 seconds, twice a day**. It interrupts your workflow and is easy to forget.

## The Solution

A physical device on your desk with **one button**:

- **Toggle down** when you arrive → Device automatically calls your API
- **Toggle up** when you leave → Logs your time
- **LED feedback** shows status and remaining hours
- **Battery powered** - lasts weeks between charges

!!! success "Annual Time Savings"
    **2.6 hours** saved + no more context switching + never forget to log time!

---

## TL;DR (for the impatient)

- **What it is**: A small ESP32-C3 desk device with a button and LED strip that calls your time-tracking API when you toggle it.
- **Build path**:
  1. Skim [Getting Started](getting-started/overview.md)
  2. Check the [Bill of Materials](hardware/bill-of-materials.md) and order parts
  3. Follow the [Assembly Guide](assembly/preparation.md)
  4. Flash the Rust firmware from `firmware/` (see [Installation](firmware/installation.md))
  5. Edit `firmware/src/config.rs` (`NETWORK_CONFIG`) to set your WiFi + API endpoint
  6. Re-flash and start using the device
- **Current limitations**: Rust firmware uses compile-time WiFi/API settings and a minimal HTTP POST client – no web config portal, deep sleep, or OTA updates yet.

---

## Features

### Hardware

- [x] **ESP32-C3** microcontroller (WiFi, low power, USB-C)
- [x] **8 RGB LEDs** (1 status + 7 energy meter)
- [x] **Toggle switch** (satisfying tactile feedback)
- [x] **2000mAh battery** (10-14 days runtime)
- [x] **USB-C charging**
- [x] **Compact size** (100×60×35mm - fits any desk)

### Firmware

- [x] WiFi connectivity using pure Rust (`esp-hal` + `esp-wifi`)
- [x] Async tasks for button, LEDs, and WiFi (Embassy executor)
- [x] Basic HTTP API integration (single POST endpoint)
- [ ] Web-based configuration portal _(planned)_
- [ ] Deep sleep mode + aggressive power saving _(planned)_
- [ ] OTA firmware updates _(planned)_

### Design

- [x] Professional appearance
- [x] 3D printable enclosure
- [x] Documented assembly process
- [x] Beginner-friendly guides
- [x] Comprehensive troubleshooting

---

## Quick Start

<div class="grid cards" markdown>

-   :material-cart:{ .lg .middle } __1. Order Components__

    ---

    Review the [Bill of Materials](hardware/bill-of-materials.md) and order parts (~$35 total).
    
    Delivery: 1-4 weeks depending on source.

-   :material-hammer-wrench:{ .lg .middle } __2. Build Device__

    ---

    Follow the [Assembly Guide](assembly/preparation.md) to build your device (2-3 hours).
    
    No advanced skills required!

-   :material-download:{ .lg .middle } __3. Flash Firmware__

    ---

    Upload firmware to ESP32-C3 using the [Installation Guide](firmware/installation.md).
    
    Takes about 30 minutes.

-   :material-cog:{ .lg .middle } __4. Configure__

    ---

    Set up WiFi and API endpoint using the [Configuration Guide](firmware/configuration.md).
    
    Quick 15-minute setup.

-   :material-party-popper:{ .lg .middle } __5. Enjoy!__

    ---

    Start using your device daily with the [Usage Guide](usage/daily-operation.md).
    
    Never type curl commands again! 🎉

</div>

---

## Project Stats

<div class="stats-grid" markdown>

| Metric | Value |
|--------|-------|
| **Total Cost** | ~$35 USD |
| **Build Time** | 2-3 hours |
| **Battery Life** | 10-14 days |
| **Lifespan** | 5+ years |
| **Weight** | ~120 grams |
| **Skill Level** | Beginner-Intermediate |

</div>

---

## Tech Stack

**Hardware**
:   ESP32-C3 microcontroller, WS2812B LEDs, LiPo battery, TP4056 charger

**Firmware**
:   Rust (`esp-hal`, Embassy, `esp-wifi`, `smart-leds`, `heapless`, `serde-json-core`)

**Connectivity**
:   WiFi 802.11 b/g/n, HTTPS, OTA updates

**Power**
:   3.7V 2000mAh LiPo, USB-C charging, deep sleep mode

**Enclosure**
:   3D printed PLA/PETG or project box

---

## Why Build This?

!!! quote "Time Saved"
    **Current process**: Open terminal, type curl command (~15 seconds × 2 times/day)
    
    **New process**: Press button (~2 seconds × 2 times/day)
    
    **Daily savings**: 26 seconds
    
    **Annual savings**: ~2.6 hours + no context switching!

Beyond time savings:

- ✅ **Tactile satisfaction** - Physical buttons feel good!
- ✅ **Never forget** - Button on your desk is impossible to miss
- ✅ **Visual feedback** - LED energy meter is motivating
- ✅ **Learn IoT** - Great project to learn hardware + firmware
- ✅ **Customizable** - Open source, modify as you like
- ✅ **Show off** - Cool desk accessory that actually works!

---

## Documentation Structure

This documentation is organized into clear sections:

**Builder path**
- [Getting Started](getting-started/overview.md) – Project overview and expectations
- [Hardware](hardware/overview.md) – Components, specs, and BOM
- [Assembly](assembly/preparation.md) – Step-by-step build and testing
- [Usage](usage/daily-operation.md) – Daily operation and maintenance

**Developer path**
- [Firmware Overview](firmware/overview.md) – Architecture and async tasks
- [Firmware Installation](firmware/installation.md) – Tooling and flashing
- [Firmware Configuration](firmware/configuration.md) – How to change WiFi + API in `config.rs`
- [`firmware/README.md`](https://github.com/lanterno/office-wall-clock/tree/main/firmware) – Source layout and dev workflow

---

## Community

!!! tip "Get Involved"
    - **Star the repo** ⭐ on [GitHub](https://github.com/lanterno/office-wall-clock)
    - **Share your build** - Post photos with #WallClockInMachine
    - **Report issues** - Help improve the project
    - **Contribute** - Submit PRs with improvements
    - **Spread the word** - Tell your friends who hate typing curl commands!

---

## License

This project is open source and available under the MIT License.

---

<div class="center-content" markdown>

## Ready to Build?

[Get Started Now](getting-started/overview.md){ .md-button .md-button--primary }
[View on GitHub](https://github.com/lanterno/office-wall-clock){ .md-button }

</div>
