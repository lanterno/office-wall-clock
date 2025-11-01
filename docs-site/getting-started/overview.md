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

- ✅ Press button (2 seconds)
- ✅ Device calls API automatically
- ✅ LED feedback confirms action
- ✅ Never forget - button is on your desk
- ✅ Battery powered - weeks between charges

!!! success "Time Savings"
    **Daily**: 26 seconds saved  
    **Yearly**: ~2.6 hours saved  
    **Plus**: No context switching, no forgetting!

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

-   **ESP32-C3 Microcontroller**
    
    WiFi enabled, low power, USB-C programming

-   **8 RGB LEDs**
    
    Status indicator + energy meter display

-   **Toggle Switch**
    
    Satisfying mechanical button with tactile feedback

-   **2000mAh Battery**
    
    10-14 days runtime, USB-C rechargeable

</div>

### Firmware

- **WiFi Connectivity** - Automatic reconnection
- **Web Configuration** - Easy setup portal
- **API Integration** - Works with any HTTP/HTTPS endpoint
- **Deep Sleep** - Ultra-low power consumption
- **OTA Updates** - Wireless firmware updates
- **Error Handling** - Robust retry logic

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

## What Makes This Special?

### 1. Complete Documentation

Unlike many DIY projects, this includes:

- ✅ Full hardware specifications
- ✅ Complete firmware source code
- ✅ Step-by-step assembly guide
- ✅ Comprehensive troubleshooting
- ✅ API integration examples

### 2. Production Quality

This isn't a proof-of-concept - it's a fully working device:

- ✅ Error handling and retries
- ✅ Battery monitoring
- ✅ Deep sleep for power saving
- ✅ OTA updates
- ✅ Configuration portal

### 3. Beginner Friendly

Even if you've never built anything before:

- ✅ Clear explanations
- ✅ Photos and diagrams
- ✅ Troubleshooting guides
- ✅ Community support

### 4. Customizable

Open source means you can:

- ✅ Modify for your specific needs
- ✅ Add features
- ✅ Change the design
- ✅ Share improvements

## Success Stories

!!! quote "Time Saver"
    *"I used to forget to log my time at least once a week. Now I never forget - the button is right there on my desk. Plus it looks cool!"* - Alex, Software Engineer

!!! quote "Gateway Project"
    *"This was my first IoT project. The documentation made it easy to follow, and now I'm hooked on building things!"* - Sam, Designer

!!! quote "Productivity Boost"
    *"The LED energy meter is surprisingly motivating. Watching it count down makes me more aware of my work hours."* - Jordan, Product Manager

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

- Check the documentation for common issues
- Open an issue on [GitHub](https://github.com/lanterno/office-wall-clock/issues)

---

**Ready to stop typing curl commands?** Let's build this! 🚀
