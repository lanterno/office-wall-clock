# Hardware Specifications

Detailed technical specifications for all components in the Wall Clock In Machine.

## System Overview

```
┌─────────────────────────────────────────────────────┐
│               Wall Clock In Machine                  │
├─────────────────────────────────────────────────────┤
│                                                      │
│  Input      ──→  Processing  ──→  Output            │
│  Toggle         ESP32-C3        8× RGB LEDs         │
│  Switch         RISC-V          WS2812B             │
│                 160MHz                               │
│                                                      │
│  Power: 3.7V LiPo ──→ 3.3V Regulated               │
│         2000mAh        AMS1117                      │
│                                                      │
│  Connectivity: WiFi 802.11 b/g/n                    │
│                HTTPS API Calls                       │
│                                                      │
└─────────────────────────────────────────────────────┘
```

## 1. Microcontroller (ESP32-C3)

### Core Specifications

| Parameter | Value | Notes |
|-----------|-------|-------|
| **CPU** | RISC-V 32-bit | Single core @ 160MHz |
| **Architecture** | RISC-V RV32IMC | Open source architecture |
| **SRAM** | 400 KB | For program execution |
| **ROM** | 384 KB | Boot code |
| **Flash** | 4 MB | External SPI flash |
| **Clock Speed** | 160 MHz | Adjustable down to 2MHz |
| **FPU** | No | Integer only |
| **Cache** | 16KB I-Cache, 16KB D-Cache | Improves performance |

### Wireless

| Parameter | Value | Notes |
|-----------|-------|-------|
| **WiFi** | 802.11 b/g/n | 2.4GHz only, no 5GHz |
| **WiFi Modes** | Station, AP, Station+AP | We use Station mode |
| **WiFi Security** | WPA/WPA2/WPA3 | Modern security |
| **Bluetooth** | BLE 5.0 | Not used in current firmware |
| **Max TX Power** | 20.5 dBm | ~100mW |
| **RX Sensitivity** | -97 dBm | Good reception |
| **Range** | 50-100m | Line of sight |

### GPIO & Peripherals

| Parameter | Value | Notes |
|-----------|-------|-------|
| **GPIO Pins** | 22 total | 15 usable (some reserved) |
| **ADC** | 6 channels, 12-bit | 0-3.3V range |
| **PWM** | 6 channels | LED dimming |
| **SPI** | 3 interfaces | For flash, external devices |
| **I2C** | 1 interface | For sensors, displays |
| **UART** | 2 interfaces | Serial communication |
| **USB** | 1× USB 2.0 OTG | Native USB-C |
| **Touch Sensors** | 14 channels | Capacitive touch |
| **RTC** | Yes | Real-time clock for timekeeping |
| **Watchdog Timer** | Yes | Auto-reset on hang |

### Power Consumption

| Mode | Current | Voltage | Power | Use Case |
|------|---------|---------|-------|----------|
| **Active (WiFi TX)** | 120mA | 3.3V | 396mW | Sending API request |
| **Active (WiFi RX)** | 100mA | 3.3V | 330mW | Receiving API response |
| **Active (CPU only)** | 25mA | 3.3V | 82.5mW | Processing, no WiFi |
| **Modem Sleep** | 15mA | 3.3V | 49.5mW | WiFi off, CPU active |
| **Light Sleep** | 1.8mA | 3.3V | 5.9mW | CPU paused, RAM retained |
| **Deep Sleep** | 5µA | 3.3V | 16.5µW | ⭐ **Used when idle** |
| **Hibernation** | 2.5µA | 3.3V | 8.25µW | RTC + minimal RAM |

**Our Usage Pattern**:
- Deep sleep 95% of time: 5µA
- Active 5% of time (button press, API, LED): ~80mA average
- **Blended average**: ~15mA over 24 hours

### Memory Map

```
0x4000_0000 ┌─────────────────┐
            │  Internal ROM   │  384KB
0x4006_0000 ├─────────────────┤
            │  Internal SRAM  │  400KB
0x400C_4000 ├─────────────────┤
            │  External Flash │  4MB
0x4200_0000 ├─────────────────┤
            │  Memory-mapped  │
            │  peripherals    │
0xFFFF_FFFF └─────────────────┘
```

### Temperature & Environmental

| Parameter | Value | Notes |
|-----------|-------|-------|
| **Operating Temp** | -40°C to +85°C | Industrial grade |
| **Storage Temp** | -40°C to +125°C | When powered off |
| **Humidity** | 5% to 95% RH | Non-condensing |
| **ESD Protection** | 2kV HBM | Human body model |

### Pin Configuration (Our Usage)

| GPIO Pin | Function | Connection | Notes |
|----------|----------|------------|-------|
| **GPIO2** | Digital Input | Toggle Switch | Pull-up enabled |
| **GPIO3** | Digital Output | WS2812B Data | 5V tolerant with resistor |
| **GPIO9** | USB D- | USB Data | Reserved for USB |
| **GPIO8** | USB D+ | USB Data | Reserved for USB |
| **EN** | Reset | Reset Button | Active low |
| **GND** | Ground | Ground plane | Multiple pins |
| **3V3** | Power Output | 3.3V supply | 600mA max |
| **5V** | Power Input | USB 5V | Only when USB connected |

**Unused Pins** (available for expansion):
- GPIO0, 1, 4, 5, 6, 7, 10, 18, 19 (9 pins free!)

## 2. LED Strip (WS2812B)

### Electrical Specifications

| Parameter | Value | Notes |
|-----------|-------|-------|
| **LED Type** | WS2812B | Integrated controller + RGB LED |
| **Package** | 5050 SMD | 5.0×5.0mm |
| **IC Protocol** | Single-wire serial | 800kHz |
| **Voltage** | 5V ±0.5V | Can work at 3.7V (dimmer) |
| **Current per LED** | 60mA max | At full white (R+G+B=255) |
| **Current typical** | 20mA | At 1/3 brightness |
| **Power per LED** | 0.3W max | Full brightness |
| **PWM Frequency** | 400Hz | Flicker-free |
| **Color Depth** | 8-bit per channel | 16.7M colors (256³) |

### Optical Specifications

| Parameter | Value | Notes |
|-----------|-------|-------|
| **Red** | 620-625nm | Dominant wavelength |
| **Green** | 515-525nm | Dominant wavelength |
| **Blue** | 465-475nm | Dominant wavelength |
| **Luminous Intensity** | Red: 550-700mcd | At 20mA |
|  | Green: 1100-1400mcd | At 20mA |
|  | Blue: 200-400mcd | At 20mA |
| **Viewing Angle** | 120° | Wide dispersion |

### Timing Requirements

| Parameter | Value | Tolerance |
|-----------|-------|-----------|
| **T0H** (0 bit high) | 0.4µs | ±150ns |
| **T0L** (0 bit low) | 0.85µs | ±150ns |
| **T1H** (1 bit high) | 0.8µs | ±150ns |
| **T1L** (1 bit low) | 0.45µs | ±150ns |
| **Reset** | >50µs | Low signal |

**Data Format**:
```
Each LED: 24 bits (GRB order)
Bit 0:    High for 0.4µs, Low for 0.85µs
Bit 1:    High for 0.8µs, Low for 0.45µs

Example: Green=255, Red=0, Blue=0
Data: [11111111][00000000][00000000]
      ↑Green    ↑Red      ↑Blue
```

### Power Budget (8 LEDs)

| Scenario | Current | Power | Notes |
|----------|---------|-------|-------|
| **All off** | 1mA | 5mW | Quiescent current |
| **1 LED dim (10%)** | 6mA | 30mW | Status indicator |
| **7 LEDs medium (25%)** | 105mA | 525mW | Energy meter |
| **All LEDs full white** | 480mA | 2.4W | Rainbow celebration |
| **Typical usage** | 60mA | 300mW | Status + 50% meter |

**Voltage Drop Consideration**:
- Long LED strips: Voltage drops 0.5V per meter
- Our 8 LEDs: Negligible drop (<0.1V)
- No need for power injection

## 3. Toggle Switch

### Mechanical Specifications

| Parameter | Value | Notes |
|-----------|-------|-------|
| **Type** | SPDT | Single Pole, Double Throw |
| **Positions** | 2 (ON-ON) | Both stable |
| **Actuation Force** | 200-300g | Tactile feedback |
| **Contact Resistance** | <50mΩ | Low resistance |
| **Insulation Resistance** | >100MΩ | High isolation |
| **Dielectric Strength** | 1000VAC | Safety |
| **Mechanical Life** | 100,000 cycles | Very durable |
| **Electrical Rating** | 3A @ 125VAC | Overkill for 3.3V |
| **Mounting** | Panel mount | 6mm threaded bushing |

### Contact Configuration

```
         ┌─── COM (Common)
    ON   │
  ┌──────┼──── NC (Normally Closed)
  │      │
  │      └──── NO (Normally Open)
  │
  └─ ON position 2

Our wiring:
  COM → GPIO2 (ESP32)
  NC  → Not connected
  NO  → GND
```

**Switch States**:
- **UP position**: COM disconnected from GND → GPIO reads HIGH (3.3V) → Clocked Out
- **DOWN position**: COM connected to GND → GPIO reads LOW (0V) → Clocked In

### Debouncing

Mechanical switches "bounce" when toggled:

```
Ideal:     ───┐              ┌───
              └──────────────┘

Reality:   ───┐┐┐┐           ┌┐┌┌──
              └┘└┘───────────┘└┘
              ↑ Bouncing (5-20ms)
```

**Software debouncing** in firmware:
- Read switch state
- Wait 50ms
- Read again to confirm
- Only register if stable

## 4. Battery (LiPo)

### Electrical Specifications

| Parameter | Value | Notes |
|-----------|-------|-------|
| **Chemistry** | Lithium Polymer | LiPo |
| **Nominal Voltage** | 3.7V | Average during discharge |
| **Fully Charged** | 4.2V | Maximum safe voltage |
| **Discharged** | 3.0V | Minimum safe voltage |
| **Capacity** | 2000mAh | At 0.2C discharge rate |
| **Discharge Rate** | 1C typical | 2A continuous |
| **Max Discharge** | 2C burst | 4A for 10 seconds |
| **Charge Rate** | 1C max | 2A charging |
| **Internal Resistance** | 80-120mΩ | Affects efficiency |
| **Cycle Life** | 500 cycles | To 80% capacity |

### Physical Specifications

| Parameter | Value | Notes |
|-----------|-------|-------|
| **Form Factor** | 503450 | 50×34×5mm (LxWxH) |
| **Weight** | 15g | Lightweight |
| **Connector** | JST-PH 2.0 | 2-pin, 2.0mm pitch |
| **Protection** | Built-in PCM | Protects against abuse |

### Discharge Curve

```
Voltage vs. Capacity
4.2V ┤●
     │ ╲
4.0V ┤  ╲___
     │      ╲___
3.7V ┤          ───___
     │                ╲___
3.3V ┤                    ╲___
     │                        ╲___
3.0V ┤                            ●
     └────────────────────────────
     0%                         100%
         Discharged Capacity
```

**Voltage to Percentage** (approximate):
- 4.2V = 100%
- 4.0V = 90%
- 3.9V = 80%
- 3.8V = 60%
- 3.7V = 40%
- 3.6V = 20%
- 3.3V = 5%
- 3.0V = 0%

### Runtime Calculation

**Average current consumption**:
```
Deep sleep (23h 55min):  5µA × 23.92h = 0.12mAh
Active (5 min/day):      80mA × 0.08h = 6.4mAh
─────────────────────────────────────────────
Total per day:                          6.52mAh

Battery capacity:        2000mAh
Days per charge:         2000 / 6.52 = 307 days
```

**Wait, 307 days?** Not quite! Reality factors:

- **LED usage** during work hours: +10mAh/day
- **WiFi reconnections**: +5mAh/day
- **API calls**: +2mAh/day
- **Efficiency losses**: +5mAh/day
- **Self-discharge**: ~1%/month

**Realistic runtime**: 10-14 days per charge

### Safety Features (PCM)

Built-in Protection Circuit Module prevents:

| Protection | Threshold | Action |
|------------|-----------|--------|
| **Overcharge** | >4.25V | Disconnect charging |
| **Overdischarge** | <2.5V | Disconnect load |
| **Overcurrent** | >3A | Disconnect temporarily |
| **Short circuit** | <0.1Ω | Disconnect immediately |
| **Over-temperature** | >80°C | Disconnect all |

### Charging Profile

```
Current/Voltage vs. Time

4.2V ┤              ___________
     │            ╱
     │          ╱  Constant Voltage
3.7V ┤        ╱
     │    ╱╱╱╱  Constant Current
     └────────────────────────
     0h   1h   2h   3h   4h

Current:
1.0A ┤────────╲
     │         ╲___
     │             ╲___
0.1A ┤                 ╲___
     └────────────────────────
     0h   1h   2h   3h   4h
```

**Stages**:
1. **Constant Current** (0-2h): Charge at 1A until 4.2V
2. **Constant Voltage** (2-3h): Hold 4.2V, current tapers
3. **Termination**: Stop when current <0.1A (100mA)

## 5. Charger (TP4056)

### Electrical Specifications

| Parameter | Value | Notes |
|-----------|-------|-------|
| **Input Voltage** | 4.5-5.5V | USB power |
| **Input Current** | 1A max | Configurable |
| **Charge Voltage** | 4.2V ±1% | Precise regulation |
| **Charge Current** | 1A default | Set by RPROG resistor |
| **Charge Termination** | 0.1A | 10% of charge current |
| **Efficiency** | 85% | Heat generation |
| **Dropout Voltage** | 0.5V | Vout = Vin - 0.5V |
| **Standby Current** | <2µA | When not charging |

### Protection Features

| Feature | Threshold | Notes |
|---------|-----------|-------|
| **Over-temperature** | 120°C | Thermal shutdown |
| **Input Overvoltage** | >6.5V | Protection |
| **Output Overvoltage** | >4.3V | Battery protection |
| **Reverse Battery** | Yes | Prevents damage |
| **Charge Timer** | Optional | Safety timeout |

### Charge Current Configuration

Charge current set by RPROG resistor:

| RPROG | Charge Current | Charge Time (2000mAh) |
|-------|----------------|----------------------|
| 1.2kΩ | 1000mA (1A) | 2-2.5 hours |
| 2kΩ   | 600mA | 3-4 hours |
| 3kΩ   | 400mA | 5-6 hours |
| 10kΩ  | 130mA | 15-20 hours |

**Formula**: `Icharge = 1200V / RPROG`

**Default**: Most TP4056 modules come with 1.2kΩ (1A charging)

### LED Indicators

| LED | State | Meaning |
|-----|-------|---------|
| **Red** | On | Charging |
| **Red** | Off | Not connected or error |
| **Blue/Green** | On | Fully charged |
| **Both** | Off | No battery |

### Pinout

```
TP4056 Module
┌─────────────┐
│ IN+    BAT+ │
│             │
│ IN-    BAT- │
└─────────────┘

IN+ → USB 5V
IN- → USB GND
BAT+ → Battery positive (JST red wire)
BAT- → Battery negative (JST black wire)
```

## 6. Voltage Regulator (AMS1117-3.3)

### Electrical Specifications

| Parameter | Value | Notes |
|-----------|-------|-------|
| **Input Voltage** | 4.5-7V | Absolute max: 15V |
| **Output Voltage** | 3.3V ±2% | Tight regulation |
| **Output Current** | 800mA | 1A absolute max |
| **Dropout Voltage** | 1.1V | Vin min = 4.4V |
| **Quiescent Current** | 5mA | Wasted as heat |
| **Load Regulation** | ±1% | Stable under load |
| **Line Regulation** | ±0.2% | Stable with Vin changes |
| **Ripple Rejection** | 75dB | Filters input noise |

### Thermal Characteristics

| Parameter | Value | Notes |
|-----------|-------|-------|
| **Thermal Resistance** | 50°C/W | Without heatsink |
| **Operating Temp** | -40°C to +125°C | Junction temp |
| **Thermal Shutdown** | 150°C | Automatic protection |
| **Power Dissipation** | 1.2W max | Without heatsink |

**Heat calculation**:
```
Power dissipated = (Vin - Vout) × Iout
Example: (4.2V - 3.3V) × 100mA = 90mW
Temperature rise: 90mW × 50°C/W = 4.5°C

Safe without heatsink ✓
```

### Capacitors Required

| Capacitor | Value | Location | Purpose |
|-----------|-------|----------|---------|
| **Input** | 10µF | VIN to GND | Stabilize input |
| **Output** | 22µF | VOUT to GND | Reduce ripple |
| **Ceramic bypass** | 0.1µF | Both sides | High-freq noise |

**Note**: Most AMS1117 modules include these capacitors already!

### Pinout

```
AMS1117 Module (Top View)
┌─────────────┐
│ VIN         │
│ GND    VOUT │
│ GND         │
└─────────────┘

VIN  → Battery positive (3.7-4.2V)
GND  → Common ground
VOUT → ESP32-C3 3.3V input
```

## System Integration

### Power Distribution

```
USB-C 5V ──→ TP4056 ──┬──→ Battery (3.7V)
                       │
                       └──→ AMS1117 ──→ ESP32-C3 (3.3V)
                            
                            ESP32 5V ──→ WS2812B LEDs (5V)
```

**Power Paths**:
1. **USB connected**: USB → TP4056 → Battery + AMS1117 → ESP32
2. **USB disconnected**: Battery → AMS1117 → ESP32
3. **LEDs**: Always powered from ESP32's 5V pin (USB) or 3.7V (battery)

### Voltage Levels

| Node | Voltage | Range | Current |
|------|---------|-------|---------|
| **USB Input** | 5.0V | 4.75-5.25V | 500mA-2A |
| **Battery** | 3.7V | 3.0-4.2V | 2000mA capacity |
| **ESP32 Input** | 3.3V | 3.0-3.6V | 80mA avg |
| **GPIO High** | 3.3V | 2.64-3.3V | 40mA max |
| **GPIO Low** | 0V | 0-0.33V | 40mA max |
| **LED Data** | 3.3V | 2.5-5.0V | <1mA |
| **LED Power** | 5.0V | 4.5-5.5V | 60mA per LED |

### Signal Levels

| Signal | Type | Voltage | Frequency |
|--------|------|---------|-----------|
| **Toggle Switch** | Digital Input | 0V / 3.3V | DC |
| **LED Data** | Serial Data | 3.3V | 800kHz |
| **WiFi RF** | Analog | N/A | 2.4GHz |
| **USB Data** | Differential | 0.3-3.6V | 12Mbps |

## Environmental Specifications

### Operating Conditions

| Parameter | Min | Typical | Max | Notes |
|-----------|-----|---------|-----|-------|
| **Temperature** | 0°C | 20°C | 40°C | Office environment |
| **Humidity** | 20% | 50% | 80% | Non-condensing |
| **Altitude** | 0m | 600m | 2000m | Lausanne is 495m |
| **Atmospheric Pressure** | 800hPa | 1013hPa | 1100hPa | Affects WiFi range |

### Storage Conditions

| Parameter | Min | Max | Notes |
|-----------|-----|-----|-------|
| **Temperature** | -20°C | +60°C | Battery separate: -40°C to +50°C |
| **Humidity** | 10% | 90% | Non-condensing |
| **Battery Storage** | 40-60% | Charge level for long-term storage |

## Compliance & Certifications

### Electromagnetic Compatibility (EMC)

- **WiFi**: FCC Part 15, CE, IC certified (via ESP32-C3 module)
- **Emissions**: Class B (residential)
- **Immunity**: IEC 61000-4 compliant

### Safety

- **Low Voltage**: USB 5V, compliant with IEC 60950
- **Battery**: UN38.3 certified (LiPo shipping)
- **RoHS**: Lead-free components

!!! warning "Certification Note"
    Personal projects don't need certifications, but components are pre-certified. If selling commercially, you'd need CE marking for Europe.

## Performance Summary

| Metric | Value | Industry Comparison |
|--------|-------|---------------------|
| **Boot Time** | 2-3 seconds | ⭐⭐⭐⭐⭐ Excellent |
| **Battery Life** | 10-14 days | ⭐⭐⭐⭐ Very Good |
| **WiFi Range** | 50-100m | ⭐⭐⭐ Good |
| **Response Time** | <500ms | ⭐⭐⭐⭐⭐ Excellent |
| **Cost** | CHF 40-90 | ⭐⭐⭐⭐⭐ Excellent |
| **Size** | 100×60×35mm | ⭐⭐⭐⭐ Compact |
| **Weight** | 85g | ⭐⭐⭐⭐ Lightweight |

## Next Steps

Now that you understand the technical specifications:

- [**Enclosure Design**](enclosure-design.md) - Physical design and 3D models
- [**Assembly Guide**](../assembly/soldering.md) - Build your device
- [**Firmware Installation**](../firmware/installation.md) - Flash the code

Or explore:

- [**Bill of Materials**](bill-of-materials.md) - Updated shopping list
- [**Wiring Diagram**](wiring.md) - Connection guide
