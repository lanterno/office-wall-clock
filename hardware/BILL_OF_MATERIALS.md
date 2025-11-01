# Bill of Materials (BOM)

**Total Cost: ~$35 USD** | **Build Time: 2-3 hours** | **Skill Level: Beginner-Intermediate**

## Where to Buy

- 🚀 **Fast (1-3 days)**: Amazon, Adafruit, SparkFun
- 💰 **Cheap (2-4 weeks)**: AliExpress, eBay
- 🏪 **Local**: Electronics stores (RadioShack alternatives)

## Core Components

### 1. Microcontroller

| Item | Specs | Qty | Price | Links |
|------|-------|-----|-------|-------|
| **ESP32-C3-DevKitM-1** | RISC-V, WiFi, USB-C | 1 | $4.00 | [AliExpress](https://www.aliexpress.com/w/wholesale-esp32-c3-devkitm-1.html) \| [Amazon](https://www.amazon.com/s?k=esp32-c3+devkit) |

**Search Terms**: "ESP32-C3 DevKitM-1" or "ESP32-C3 development board"

**What to Look For**:
- ✅ USB-C connector (NOT micro-USB)
- ✅ On-board antenna
- ✅ CH340 or CP2102 USB chip (or native USB)
- ✅ Pin headers included or pre-soldered

**Alternative**: ESP32-C3-Mini-1 module (if you want smaller/bare chip)

---

### 2. LED Strip

| Item | Specs | Qty | Price | Links |
|------|-------|-----|-------|-------|
| **WS2812B LED Strip** | Addressable RGB, 60 LEDs/m | 8 LEDs | $3.00 | [Amazon](https://www.amazon.com/s?k=ws2812b+led+strip) \| [AliExpress](https://www.aliexpress.com/w/wholesale-ws2812b.html) |

**Search Terms**: "WS2812B LED strip" or "NeoPixel LED strip"

**What to Buy**:
- Buy a 1-meter strip (60 LEDs) and cut to 8 LEDs
- Waterproof (IP65) or non-waterproof (IP20) - both work
- Black PCB preferred (looks better)
- 5V version (NOT 12V)

**Cutting Guide**: LEDs have cut marks every 3 LEDs. Cut after 8th LED, save rest for future projects!

---

### 3. Button/Switch

| Item | Specs | Qty | Price | Links |
|------|-------|-----|-------|-------|
| **Toggle Switch SPDT** | 12mm panel mount, metal | 1 | $4.00 | [Amazon](https://www.amazon.com/s?k=12mm+toggle+switch+spdt) |

**Search Terms**: "12mm toggle switch SPDT metal" or "panel mount toggle switch"

**What to Look For**:
- ✅ SPDT (Single Pole Double Throw) - 3 terminals
- ✅ 12mm mounting hole diameter
- ✅ Metal construction (feels premium)
- ✅ Flat or round toggle (your preference!)
- ✅ ON-ON type (maintained position)

**Color Options**: Silver, black, gold - pick what matches your design!

**Alternative**: Illuminated toggle switch (has built-in LED) - costs $6-8

---

### 4. Battery

| Item | Specs | Qty | Price | Links |
|------|-------|-----|-------|-------|
| **LiPo Battery** | 3.7V, 2000mAh, JST connector | 1 | $8.00 | [Amazon](https://www.amazon.com/s?k=3.7v+2000mah+lipo+battery+jst) |

**Search Terms**: "3.7V 2000mAh LiPo battery JST"

**What to Look For**:
- ✅ 2000-2500 mAh capacity
- ✅ JST-PH 2.0mm connector (red/black wires)
- ✅ Protection circuit (PCB on battery)
- ✅ Dimensions fit your enclosure (~50×30×10mm)
- ⚠️ **Buy from reputable seller** - safety matters!

**Safety Note**: LiPo batteries can be dangerous if damaged. Handle with care, don't puncture!

---

### 5. Battery Charger

| Item | Specs | Qty | Price | Links |
|------|-------|-----|-------|-------|
| **TP4056 Charger Module** | USB-C, 1A charge, protection | 1 | $1.50 | [Amazon](https://www.amazon.com/s?k=tp4056+usb-c+charger) \| [AliExpress](https://www.aliexpress.com/w/wholesale-tp4056-usb-c.html) |

**Search Terms**: "TP4056 USB-C lithium battery charger module"

**What to Look For**:
- ✅ USB-C input (NOT micro-USB)
- ✅ Protection features (DW01A chip visible)
- ✅ Red/Blue indicator LEDs
- ✅ Small form factor (~26×17mm)

**Alternative**: IP5306 charger module (has 5V boost output too)

---

### 6. Voltage Regulator

| Item | Specs | Qty | Price | Links |
|------|-------|-----|-------|-------|
| **AMS1117-3.3 Module** | LDO regulator, 3.3V output | 1 | $1.00 | [Amazon](https://www.amazon.com/s?k=ams1117+3.3v+module) \| [AliExpress](https://www.aliexpress.com/w/wholesale-ams1117-3.3v.html) |

**Search Terms**: "AMS1117-3.3V regulator module" or "3.3V LDO module"

**What to Look For**:
- ✅ 3.3V output
- ✅ 500mA+ current rating
- ✅ Pre-built module (easier than bare IC)
- ✅ Screw terminals or pin headers

**Alternative**: HT7333 (better low dropout) or use ESP32's built-in regulator

---

### 7. USB-C Connector

| Item | Specs | Qty | Price | Links |
|------|-------|-----|-------|-------|
| **USB-C Panel Mount** | Female, with cable/PCB | 1 | $2.00 | [Amazon](https://www.amazon.com/s?k=usb-c+panel+mount+connector) |

**Search Terms**: "USB-C panel mount connector female"

**What to Look For**:
- ✅ Female connector (male USB-C cable plugs into it)
- ✅ Mounting holes or nut for panel
- ✅ ~20cm cable attached (easier to wire)
- ✅ Power-only (don't need data pins)

---

## Electronic Components

### Passive Components Kit

| Item | Specs | Qty | Price | Links |
|------|-------|-----|-------|-------|
| **Capacitor Kit** | 0.1µF, 10µF, 100µF variety | 1 kit | $5.00 | [Amazon](https://www.amazon.com/s?k=capacitor+assortment+kit) |
| **Resistor Kit** | 1/4W, assorted values | 1 kit | $5.00 | [Amazon](https://www.amazon.com/s?k=resistor+assortment+kit) |

**Or Buy Individual Components:**

| Component | Value | Qty | Purpose |
|-----------|-------|-----|---------|
| Electrolytic Capacitor | 100µF, 16V | 2 | Power smoothing |
| Ceramic Capacitor | 10µF, 16V | 2 | Bypass caps |
| Ceramic Capacitor | 0.1µF | 4 | Decoupling |
| Resistor | 10kΩ | 2 | Pull-up |
| Resistor | 330Ω | 1 | LED limiter |
| Diode | 1N4148 | 1 | Reverse protection |

💡 **Tip**: Buy a variety kit if this is your first electronics project. You'll use them in future projects!

---

## Wiring & Connectors

| Item | Specs | Qty | Price | Links |
|------|-------|-----|-------|-------|
| **Silicone Wire** | 24 AWG, red+black | 2m each | $4.00 | [Amazon](https://www.amazon.com/s?k=24+awg+silicone+wire) |
| **JST Connectors** | 2-pin, 2.0mm pitch | 5 | $3.00 | [Amazon](https://www.amazon.com/s?k=jst+ph+2.0+connector+kit) |
| **Heat Shrink Tubing** | Assorted sizes | 1 kit | $5.00 | [Amazon](https://www.amazon.com/s?k=heat+shrink+tubing+kit) |
| **Jumper Wires** | Male-to-female, 20cm | 10 | $3.00 | [Amazon](https://www.amazon.com/s?k=dupont+jumper+wires) |

---

## Enclosure

### Option 1: 3D Printed (Recommended)

| Item | Material | Cost | Links |
|------|----------|------|-------|
| **3D Print Service** | PLA filament | $5-10 | [Craftcloud](https://craftcloud3d.com/) \| [Shapeways](https://www.shapeways.com/) |
| **Or Print Yourself** | PLA roll, 1kg | $20 | [Amazon](https://www.amazon.com/s?k=pla+filament) |

**Files Provided**: STL files in `hardware/enclosure/` directory

**Print Settings**:
- Layer Height: 0.2mm
- Infill: 20%
- Supports: Yes (for overhang areas)
- Material: PLA or PETG

### Option 2: Pre-Made Enclosure

| Item | Specs | Cost | Links |
|------|-------|------|-------|
| **Project Box** | 100×60×35mm ABS | $6.00 | [Amazon](https://www.amazon.com/s?k=plastic+project+box+100x60) |

**Modifications Needed**:
- Drill holes for toggle switch (12mm)
- Cut slot for USB-C connector
- Cut window for LED strip

---

## Hardware & Fasteners

| Item | Specs | Qty | Cost |
|------|-------|-----|------|
| **M3 Screws** | 8mm length | 8 | $2.00 |
| **M3 Hex Nuts** | Standard | 8 | $1.00 |
| **M3 Standoffs** | 10mm height | 4 | $2.00 |
| **Rubber Feet** | Self-adhesive, 10mm | 4 | $2.00 |

[Amazon Kit](https://www.amazon.com/s?k=m3+screw+standoff+kit) - $8 for complete assortment

---

## Tools Required

### Essential Tools (Must Have)

| Tool | Approximate Cost | Links |
|------|------------------|-------|
| **Soldering Iron** | $15-25 | [Amazon](https://www.amazon.com/s?k=soldering+iron+kit) |
| **Solder** | $8 | [Amazon](https://www.amazon.com/s?k=lead+free+solder) |
| **Wire Strippers** | $10 | [Amazon](https://www.amazon.com/s?k=wire+stripper) |
| **Screwdriver Set** | $10 | [Amazon](https://www.amazon.com/s?k=precision+screwdriver+set) |
| **Multimeter** | $15 | [Amazon](https://www.amazon.com/s?k=digital+multimeter) |
| **USB-C Cable** | $5 | [Amazon](https://www.amazon.com/s?k=usb-c+cable) |

**Total Tool Cost**: ~$70 (one-time investment, use for many projects!)

### Nice to Have

| Tool | Purpose | Cost |
|------|---------|------|
| **Helping Hands** | Hold PCBs while soldering | $10 |
| **Hot Glue Gun** | Strain relief, mounting | $8 |
| **Flush Cutters** | Clean wire cuts | $8 |
| **Tweezers** | Handle small parts | $5 |
| **Desoldering Pump** | Fix mistakes | $5 |
| **Magnifying Glass** | See tiny components | $12 |

---

## Software (Free!)

| Software | Purpose | Links |
|----------|---------|-------|
| **Rust toolchain (rustup)** | Build firmware | [rustup.rs](https://rustup.rs) |
| **espflash** | Flash firmware & monitor serial | [esp-rs/espflash](https://github.com/esp-rs/espflash) |
| **VS Code** | Code editing | [code.visualstudio.com](https://code.visualstudio.com/) |
| **Fusion 360** | 3D design (optional) | [autodesk.com](https://www.autodesk.com/products/fusion-360/personal) |

---

## Shopping List Summary

### Quick Copy-Paste List for Amazon Cart

```
- ESP32-C3 development board
- WS2812B LED strip (1 meter, 60 LEDs)
- 12mm SPDT toggle switch
- 3.7V 2000mAh LiPo battery with JST connector
- TP4056 USB-C charger module
- AMS1117-3.3V voltage regulator module
- USB-C panel mount connector female
- 24 AWG silicone wire (red and black)
- JST connector kit
- Heat shrink tubing assortment
- M3 screw/nut/standoff kit
- Rubber feet (4 pack)
- Soldering iron kit (if needed)
- Lead-free solder
- Wire strippers
- Multimeter
- USB-C cable
```

### Estimated Delivery Times

| Source | Delivery | Shipping Cost | Total Time |
|--------|----------|---------------|------------|
| **Amazon Prime** | 1-2 days | Free | 2-3 days |
| **Amazon Regular** | 5-7 days | Free/$5 | 1 week |
| **AliExpress** | 15-30 days | Free | 3-5 weeks |
| **Local Store** | Same day | Gas money | 1 day |

💡 **Pro Tip**: Order from AliExpress for ~40% savings, but plan 3-4 weeks ahead!

---

## Cost Optimization Strategies

### Budget Build (~$25)
- Buy from AliExpress (wait time)
- Use existing USB cable cut up for wiring
- Skip voltage regulator (power ESP32 directly from TP4056's 4.2V output - works!)
- Use cardboard box as enclosure (functional, not pretty)
- Borrow tools from friends/makerspace

### Premium Build (~$50)
- Buy from Amazon (fast delivery)
- Get illuminated toggle switch ($8)
- Larger 3000mAh battery ($12)
- Custom powder-coated aluminum enclosure ($20)
- Wireless charging module ($8)

---

## Buying Tips

### Red Flags 🚩
- ESP32 board without USB connector (needs programmer)
- LiPo battery with no protection circuit
- Extremely cheap chargers (fire hazard)
- 12V LED strips (won't work with 5V system)

### Good Signs ✅
- Seller has 95%+ rating
- Product has many reviews with photos
- Includes datasheets/documentation
- Ships from same country (faster)

---

## Alternative Component Options

### Different Microcontroller Options

| Board | When to Use | Price |
|-------|-------------|-------|
| **ESP32-C3** (recommended) | Best balance of features | $4 |
| **ESP32-S2** | Need more GPIO pins | $5 |
| **ESP8266 D1 Mini** | Budget build, less features | $3 |
| **Arduino Nano 33 IoT** | Want Arduino ecosystem | $20 |

### Different Battery Options

| Battery | Capacity | Runtime | Price |
|---------|----------|---------|-------|
| **1000mAh** | Smaller | 5-7 days | $5 |
| **2000mAh** (recommended) | Standard | 12-14 days | $8 |
| **3000mAh** | Larger | 20+ days | $12 |

---

## Next Steps

1. ✅ Copy the shopping list above
2. 🛒 Order components (start with AliExpress if patient)
3. ⏰ While waiting (2-4 weeks), read the [Assembly Guide](../docs/ASSEMBLY_GUIDE.md)
4. 💻 Set up development environment (see [Firmware Installation](../docs/FIRMWARE_INSTALLATION.md))
5. 🎨 Design or print the enclosure
6. ☕ Relax - you're about to build something awesome!

---

**Questions about components?** Check the [FAQ](../docs/FAQ.md) or open an issue!

**Found better prices?** Submit a PR to update this list!
