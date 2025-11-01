# Hardware Specifications

## Overview

This document details the technical specifications and component selection rationale for the Wall Clock In Machine.

## Design Requirements

### Functional Requirements
- Single button for clock in/out
- Visual feedback via LEDs
- WiFi connectivity for API communication
- 8+ hours battery life
- Automatic charging via USB-C
- Compact desktop form factor

### Technical Requirements
- WiFi 802.11 b/g/n (2.4GHz)
- HTTPS support for secure API calls
- Button debouncing
- Low power sleep modes
- Battery level monitoring

## Microcontroller Selection

### Chosen: ESP32-C3-DevKitM-1

**Rationale**: The ESP32-C3 is the perfect choice for this project.

#### Specifications
- **CPU**: RISC-V single-core 32-bit @ 160MHz
- **RAM**: 400 KB SRAM
- **Flash**: 4 MB
- **WiFi**: 802.11 b/g/n (2.4 GHz)
- **Bluetooth**: Bluetooth 5 (LE)
- **GPIO**: 22 programmable GPIOs
- **USB**: Native USB Serial/JTAG (no UART bridge needed!)
- **Power**: Deep sleep mode at 5 µA
- **Form Factor**: 25.4 × 43.2 mm
- **Price**: ~$3-5

#### Why ESP32-C3?

✅ **Built-in WiFi**: No additional modules needed  
✅ **Native USB**: Direct USB-C programming without FTDI chip  
✅ **Low Power**: Deep sleep mode extends battery life  
✅ **Rust + ESP-IDF Support**: Modern, safe firmware with great tooling  
✅ **Affordable**: Great value for features  
✅ **Compact**: Small footprint for enclosure  
✅ **Active Community**: Tons of examples and libraries  

#### Alternatives Considered

| Board | Pros | Cons | Verdict |
|-------|------|------|---------|
| **Arduino Nano 33 IoT** | Easy to use, 3.3V logic | More expensive (~$20), larger | ❌ Overkill |
| **ESP8266** | Cheaper, WiFi | Older, less GPIO, no USB | ❌ Outdated |
| **ESP32 (original)** | More powerful | Larger, higher power, no USB | ❌ Unnecessary |
| **Raspberry Pi Pico W** | New, interesting | Needs more external components | ❌ More complex |

## LED System

### Chosen: WS2812B NeoPixel LED Strip (8 LEDs)

**Purpose**: Status indicator + Energy meter

#### Specifications
- **Type**: Addressable RGB LEDs
- **LEDs**: 8 individual pixels
- **Voltage**: 5V
- **Current**: ~60mA per LED at full white
- **Protocol**: Single-wire serial (easy!)
- **Refresh Rate**: 400 Hz+
- **Form Factor**: Flexible strip, cuttable

#### LED Layout Design

```
┌─────────────────────────────────┐
│  [🔴] [⚪] [⚪] [⚪] [⚪] [⚪] [⚪] [⚪]  │  8 LEDs
│   ^                            ^   │
│   │                            │   │
│ Status                    Energy   │
│  LED                       Meter   │
└─────────────────────────────────┘
```

**LED 0 (Status LED)**: 
- 🔴 Red: Clocked out
- 🟢 Green: Clocked in
- 🔵 Blue: Connecting to WiFi
- 🟡 Yellow: API error
- 🟣 Purple: Charging

**LEDs 1-7 (Energy Meter)**: Show remaining hours
- 8 hours = 7 LEDs lit (full energy)
- 1 hour = 1 LED lit (almost done!)
- 0 hours = Celebration animation! 🎉

#### Color Scheme for Energy Meter

Progressive "thermal" gradient:
- 🟢🟢🟢🟢 (7-5 hours): Full energy - Green
- 🟡🟡🟡 (4-3 hours): Mid-day - Yellow/Orange  
- 🔴🔴 (2-1 hours): Running low - Orange/Red

#### Why NeoPixels?

✅ **Single Pin Control**: Only needs 1 GPIO pin  
✅ **Individual Addressing**: Full control of each LED  
✅ **Smooth Animations**: Easy to create effects  
✅ **Bright & Visible**: Clear in office lighting  
✅ **No Resistors Needed**: Built-in drivers  
✅ **Widely Available**: Cheap and reliable  

## Button

### Chosen: Illuminated Toggle Switch (SPDT)

**Purpose**: Physical clock in/out control with satisfying feedback

#### Specifications
- **Type**: Single Pole Double Throw (SPDT) with LED
- **Action**: Maintained (stays in position)
- **Mounting**: 12mm panel mount
- **LED**: 12V built-in (we'll add external LED)
- **Rating**: 3A @ 125VAC (way more than we need)
- **Lifetime**: 50,000+ cycles (137 years of daily use!)

#### Why Toggle Switch vs Push Button?

| Feature | Toggle | Push Button | Winner |
|---------|--------|-------------|--------|
| **Physical State** | Shows status | Needs LED | ✅ Toggle |
| **Tactile Feel** | Very satisfying | Varies | ✅ Toggle |
| **Accidental Press** | Harder | Easier | ✅ Toggle |
| **Visual Design** | Industrial cool | Common | ✅ Toggle |
| **User Intent** | Clear ON/OFF | Ambiguous | ✅ Toggle |

The toggle switch physically represents your work state - you can see at a glance if you're clocked in!

## Power System

### Battery: 3.7V 2000mAh LiPo

#### Specifications
- **Capacity**: 2000 mAh
- **Voltage**: 3.7V nominal (3.0-4.2V range)
- **Chemistry**: Lithium Polymer
- **Connector**: JST-PH 2.0mm
- **Dimensions**: ~50 × 30 × 10 mm
- **Weight**: ~35g
- **Cycles**: 300-500 charge cycles

#### Battery Life Calculation

**Power Consumption**:
- ESP32-C3 active (WiFi): 80mA
- ESP32-C3 deep sleep: 5µA ≈ 0.005mA
- LEDs (1 status + 3 energy avg): 120mA
- Average per hour: ~15mA (mostly sleeping)

**Battery Life**:
- 2000mAh ÷ 15mA = **133 hours** = ~16 work days
- With conservative estimate: **10-14 days** between charges

### Charging: TP4056 LiPo Charger Module

#### Specifications
- **Input**: 5V USB-C
- **Charge Current**: 1A (adjustable with resistor)
- **Protection**: Overcharge, over-discharge, short circuit
- **Indicator LEDs**: Charging (red), Complete (blue)
- **Voltage**: Charges to 4.2V, cutoff at 3.0V
- **Size**: 26 × 17 mm

#### Why TP4056?

✅ **Safe**: Built-in battery protection  
✅ **Simple**: 2 wires in, 2 wires out  
✅ **Cheap**: ~$1 per module  
✅ **Reliable**: Proven design, millions sold  
✅ **Status LEDs**: Know when charging is done  

### Voltage Regulation: LDO 3.3V Regulator

The ESP32-C3 needs 3.3V, but our battery is 3.7V (and varies 3.0-4.2V).

#### Specifications
- **Input**: 3.0V - 5.5V
- **Output**: 3.3V @ 500mA
- **Dropout**: 300mV (works even when battery is low)
- **Quiescent Current**: 5µA (doesn't waste battery)
- **Protection**: Thermal shutdown, current limiting
- **Module**: AMS1117-3.3 or HT7333

## Connectivity Options

### Primary: WiFi

**Rationale**: Built into ESP32-C3, no additional hardware needed.

**Advantages**:
- Direct internet access
- Can work without laptop nearby
- Firmware updates over-the-air (OTA)
- No pairing required

**Implementation**:
- Store WiFi credentials in flash memory
- Reconnect automatically on boot
- Fallback to AP mode for initial setup
- HTTPS for secure API communication

### Secondary: Bluetooth (Future Feature)

**Rationale**: Could be useful for initial setup or laptop-tethered operation.

**Potential Use Cases**:
- Configure WiFi credentials via phone app
- Work without WiFi (sync via Bluetooth to laptop)
- Battery level monitoring on phone

**Status**: 🔮 Not implemented in v1.0, but hardware supports it!

## Additional Components

### Passive Components

| Component | Value | Quantity | Purpose |
|-----------|-------|----------|---------|
| **Capacitor** | 100µF electrolytic | 2 | Power supply smoothing |
| **Capacitor** | 10µF ceramic | 2 | Bypass caps for ICs |
| **Capacitor** | 0.1µF ceramic | 4 | Decoupling |
| **Resistor** | 10kΩ | 2 | Pull-up for button |
| **Resistor** | 330Ω | 1 | LED current limiting |
| **Diode** | 1N4148 | 1 | Reverse polarity protection |

### Connectors & Wiring

| Component | Type | Purpose |
|-----------|------|---------|
| **USB-C Connector** | Female panel mount | Charging port |
| **JST Connector** | 2-pin 2.0mm | Battery connection |
| **Wire** | 24 AWG silicone | Internal wiring |
| **Header Pins** | 2.54mm pitch | Breadboard-friendly connections |

## Enclosure Requirements

See [ENCLOSURE_DESIGN.md](ENCLOSURE_DESIGN.md) for full details.

### Constraints
- **Minimum Internal Dimensions**: 80 × 50 × 30 mm
- **Material**: 3D printed PLA or ABS
- **Access**: USB-C port on side
- **Button**: Top-mounted toggle switch
- **LEDs**: Front-facing light pipe or translucent panel
- **Weight**: Target < 150g total

### Mounting
- **Rubber feet**: Prevent sliding on desk
- **Optional**: Wall-mount holes on back

## Development Tools Required

### Hardware Tools
- Soldering iron (30W+)
- Solder (lead-free recommended)
- Wire strippers
- Small screwdriver set
- Multimeter
- USB-C cable
- Helping hands / PCB holder
- Heat shrink tubing

### Software Tools
- **Rust toolchain (rustup)**: Firmware development
- **espflash**: Flashing firmware and serial monitor
- **Web Browser**: Initial device configuration

### Optional Tools
- 3D printer (or use online service)
- Hot glue gun
- Dremel for enclosure modifications
- Logic analyzer for debugging

## Safety Considerations

### Electrical Safety
⚠️ **LiPo Battery**: Can be dangerous if punctured, overcharged, or shorted
- Always use the TP4056 protection circuit
- Don't short the battery terminals
- Charge in a fireproof container first time
- Stop using if battery swells

### Construction Safety
- Work in ventilated area (solder fumes)
- Wear safety glasses
- Don't touch soldering iron tip (seriously)
- Check polarity before connecting power

## Testing Checklist

Before assembling into enclosure:

- [ ] Battery charges correctly (LED indicators work)
- [ ] ESP32-C3 boots and connects to WiFi
- [ ] Button press detected reliably
- [ ] All 8 LEDs light up correctly
- [ ] API calls succeed
- [ ] Deep sleep mode works
- [ ] Battery lasts expected time
- [ ] USB-C charging works through panel connector

## Cost Breakdown

| Component | Price (USD) | Source |
|-----------|-------------|--------|
| ESP32-C3 DevKitM-1 | $4.00 | AliExpress/Amazon |
| WS2812B LED Strip (8 LEDs) | $3.00 | AliExpress |
| Toggle Switch | $4.00 | Amazon |
| 2000mAh LiPo Battery | $8.00 | Amazon |
| TP4056 Charger Module | $1.50 | AliExpress |
| USB-C Panel Connector | $2.00 | Amazon |
| LDO 3.3V Regulator | $1.00 | AliExpress |
| Passive Components Kit | $3.00 | AliExpress |
| Enclosure (3D print) | $5.00 | Material cost |
| Misc (wire, solder, etc.) | $3.00 | - |
| **TOTAL** | **~$34.50** | |

*Prices approximate and vary by region. Buying from AliExpress saves money but takes 2-4 weeks.*

## Power Budget Analysis

### Detailed Current Draw

| State | Duration | Current | Energy |
|-------|----------|---------|--------|
| **API Call** | 2 sec | 120 mA | 0.067 mAh |
| **LED Update** | 5 sec | 100 mA | 0.139 mAh |
| **Deep Sleep** | 8 hours | 0.005 mA | 0.040 mAh |
| **Daily Total** | - | - | ~0.5 mAh |

### Battery Life Projection

**Scenario 1: Typical Use**
- 2 button presses/day (clock in/out)
- LEDs on for 8 hours (energy meter)
- Deep sleep when not displaying
- **Battery Life**: 12-14 days

**Scenario 2: Heavy Use**
- Multiple check-ins throughout day
- LEDs always bright
- Frequent API sync
- **Battery Life**: 7-10 days

**Scenario 3: Idle**
- No button presses
- Deep sleep most of the time
- **Battery Life**: 30+ days

## Next Steps

1. 📋 Review the [Bill of Materials](BILL_OF_MATERIALS.md)
2. 🛒 Order all components
3. 📦 While waiting, review [Assembly Guide](../docs/ASSEMBLY_GUIDE.md)
4. 🎨 Design your enclosure (or use reference design)
5. 💻 Set up development environment

---

**Questions?** Check the [Troubleshooting Guide](../docs/TROUBLESHOOTING.md) or open an issue!
