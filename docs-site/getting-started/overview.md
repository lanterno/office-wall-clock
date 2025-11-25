# Overview

Welcome to the Wall Clock In Machine project! This guide will help you understand what this project is about and whether it's right for you.

## What Is This?

The Wall Clock In Machine is a **physical IoT device** that automates time tracking for office workers. Instead of typing terminal commands to start/stop your work timer, you simply press a button on your desk.

### The Problem It Solves

If you use a timer API to track your work hours, you probably do this every day:

```bash
# When arriving at office
curl -X POST https://your-api.com/api/timer/start \
  -H "Content-Type: application/json" \
  -d '{"project_id": "office-time"}'

# When leaving office  
curl -X POST https://your-api.com/api/timer/stop \
  -H "Content-Type: application/json" \
  -d '{"beat_id": "12345"}'
```

This process:

- ❌ Takes 15 seconds (twice a day)
- ❌ Interrupts your workflow
- ❌ Easy to forget
- ❌ Requires opening terminal
- ❌ Frustrating on busy days

### The Solution

With the Wall Clock In Machine:

- Press a physical toggle switch instead of typing curl commands.
- Device calls your API automatically and shows state via LEDs.

## Who Is This For?

This project is perfect for you if:

- ✅ You track work time using an API/service
- ✅ You're tired of typing terminal commands
- ✅ You like physical buttons and tactile feedback
- ✅ You enjoy DIY electronics projects
- ✅ You want to learn IoT development
- ✅ You have basic soldering skills (or want to learn)

### Skill Level

**Beginner to Intermediate**

- Basic electronics knowledge helpful but not required
- Never soldered before? Our guides teach you!
- Comfortable with command line is useful
- No programming required (Rust firmware is ready to flash)

### Time Investment

| Phase | Time Required |
|-------|---------------|
| **Reading Documentation** | 2-3 hours |
| **Ordering Components** | 1 hour |
| **Waiting for Delivery** | 1-4 weeks |
| **Assembly** | 2-3 hours |
| **Firmware Setup** | 30 minutes |
| **Configuration** | 15 minutes |
| **Total Active Time** | ~5 hours |

## Project Features

### Hardware

<div class="grid cards" markdown>

-   **ESP32-C6 DevKitC-1 Microcontroller**
    
    WiFi 6 enabled, low power, USB-C programming

-   **8 RGB LEDs**
    
    Status indicator + energy meter display

-   **Toggle Switch**
    
    Satisfying mechanical button with tactile feedback

-   **2000mAh Battery**
    
    10-14 days runtime, USB-C rechargeable

</div>

### Firmware

- **WiFi Connectivity** – Connects to a single configured network
- **Async Tasks** – Separate tasks for button, LEDs, and WiFi using Embassy
- **Basic API Integration** – Simple HTTP POST to your timer API
- _Planned_: Web configuration portal, deep sleep, OTA updates, and richer error handling

### Design

- **Professional Appearance** - Looks good on any desk
- **Compact Size** - 100×60×35mm (about size of deck of cards)
- **3D Printable** - STL files included
- **Open Source** - Modify as you like
- **Well Documented** - Step-by-step guides for everything

## What You'll Need

### Tools Required

| Tool | Cost | Where to Buy |
|------|------|--------------|
| Soldering Iron | $15-25 | Amazon |
| Solder | $8 | Amazon |
| Wire Strippers | $10 | Amazon |
| Multimeter | $15 | Amazon |
| Screwdriver Set | $10 | Amazon |
| USB-C Cable | $5 | Amazon |
| **Total** | **~$70** | *One-time investment* |

!!! tip "Already Have Tools?"
    If you have basic electronics tools, you're all set! If not, this is a great starter kit that you'll use for many projects.

### Components Required

**Total Cost**: ~$35

See [Bill of Materials](../hardware/bill-of-materials.md) for complete shopping list with links.

### Software Required (Free!)

- **Code Editor**: VS Code (recommended)
- **Rust toolchain**: For firmware development
- **espflash**: For flashing and serial monitor

All software is free and open source!

## Prerequisites

### Technical Requirements

**Your Timer API Must Have**:

- ✅ HTTP/HTTPS endpoint for starting timer
- ✅ HTTP/HTTPS endpoint for stopping timer
- ✅ JSON API (or be willing to modify firmware)
- ✅ Accessible from your WiFi network

**Example API Format**:
```json
POST /api/timer/start
{
  "project_id": "office-time"
}

POST /api/timer/stop
{
  "beat_id": "12345"
}
```

!!! info "API Flexibility"
    The firmware is designed to work with the API structure shown above, but you can easily modify it to match your specific API. See [API Integration](../firmware/api-integration.md) for details.

### Knowledge Requirements

**Helpful to Know** (but not required):

- Basic electronics (what is voltage, current, ground)
- Soldering (or watch a YouTube tutorial first)
- Command line basics (cd, ls, running commands)
- ESP-IDF + Rust basics (helpful for troubleshooting)

**Don't Worry If You Don't Know**:

Our documentation explains everything step-by-step with:

- Clear instructions with photos/diagrams
- Troubleshooting for common issues
- Beginner-friendly explanations
- No assumptions about prior knowledge

## Project Structure

The complete project includes:

```
office-wall-clock/
├── hardware/           # Component specs and BOM
├── firmware/           # Complete Rust source code
├── docs-site/          # This documentation website
├── tools/              # Helper scripts and utilities
└── README.md           # Quick overview
```

## What Makes This Useful

- Hardware, firmware, and docs are all included in this repo.
- The design is simple enough for a first IoT build but still non-trivial.
- All code is open source, so you can adapt it to your own API or LEDs.

## Next Steps

Ready to get started?

1. **Read the [Quick Start Guide](quick-start.md)** - 5-minute overview
2. **Review [Project Timeline](timeline.md)** - Plan your build
3. **Check [Bill of Materials](../hardware/bill-of-materials.md)** - See what to buy
4. **Order Components** - Get parts on the way
5. **Start Building!** - Follow assembly guides

<div class="center-content" markdown>

[Quick Start Guide](quick-start.md){ .md-button .md-button--primary }
[View Project on GitHub](https://github.com/lanterno/office-wall-clock){ .md-button }

</div>

## Questions?

- Check the documentation for common issues.
- Open an issue on [GitHub](https://github.com/lanterno/office-wall-clock/issues).
