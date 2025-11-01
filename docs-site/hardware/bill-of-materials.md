# Bill of Materials (BOM) - Switzerland Edition 🇨🇭

**Total Cost: ~CHF 90-100** (Swiss suppliers) | **Build Time: 2-3 hours** | **Skill Level: Beginner-Intermediate**

Complete shopping list for building the Wall Clock In Machine, optimized for Switzerland with Swiss suppliers, CHF pricing, and all components needed for testing and development.

## Quick Shopping Strategy

### Option 1: Fast Build (1-3 days, CHF 90-100)
- **Digitec Galaxus** + **Conrad.ch** (online)
- Professional components, fast delivery
- Free shipping over CHF 50

### Option 2: Budget Build (3-4 weeks, CHF 45-50)
- Order from China (AliExpress/eBay) - single order to minimize customs
- Split orders to stay under CHF 62 limit
- Best for patient builders

### Option 3: Premium Build (1-2 days, CHF 150)
- **FabLab EPFL** + **Digitec** (in-person)
- Workshop access + professional components
- Community support included

---

## Core Components

### 1. Microcontroller

| Item | Specs | Qty | Price (CHF) | Suppliers |
|------|-------|-----|-------------|-----------|
| **ESP32-C3-DevKitM-1** | RISC-V, WiFi, USB-C | 1 | CHF 12-18 | Digitec \| Conrad \| Distrelec |

**Where to Buy**:
- **Digitec Galaxus**: CHF 15-18, free shipping over CHF 50, 1-2 day delivery - [digitec.ch](https://www.digitec.ch/)
- **Conrad.ch**: CHF 14-16, free shipping over CHF 50, 2-3 day delivery - [conrad.ch](https://www.conrad.ch/)
- **Distrelec**: CHF 16-20, professional components, 1-2 day delivery - [distrelec.ch](https://www.distrelec.ch/)
- **Play Zone** (Lausanne, Centre Flon): In-store pickup - [playzone.ch](https://www.playzone.ch/)

**What to Look For**:
- ✅ USB-C connector (NOT micro-USB)
- ✅ On-board antenna
- ✅ CH340 or CP2102 USB chip (or native USB)
- ✅ Pin headers included or pre-soldered

---

### 2. LED Strip

| Item | Specs | Qty | Price (CHF) | Suppliers |
|------|-------|-----|-------------|-----------|
| **WS2812B LED Strip** | Addressable RGB, 60 LEDs/m | 8 LEDs (buy 1m strip) | CHF 8-15 | Digitec \| Conrad |

**Where to Buy**:
- **Digitec Galaxus**: CHF 12-15 for 1m strip - [digitec.ch](https://www.digitec.ch/)
- **Conrad.ch**: CHF 10-12 for 1m strip - [conrad.ch](https://www.conrad.ch/)

**What to Buy**:
- Buy a 1-meter strip (60 LEDs) and cut to 8 LEDs
- Waterproof (IP65) or non-waterproof (IP20) - both work
- Black PCB preferred (looks better)
- 5V version (NOT 12V)

**Cutting Guide**: LEDs have cut marks every 3 LEDs. Cut after 8th LED, save rest for future projects!

---

### 3. Button/Switch

| Item | Specs | Qty | Price (CHF) | Suppliers |
|------|-------|-----|-------------|-----------|
| **Toggle Switch SPDT** | 12mm panel mount, metal | 1 | CHF 5-8 | Conrad \| Distrelec |

**Where to Buy**:
- **Conrad.ch**: CHF 6-8, quality switches - [conrad.ch](https://www.conrad.ch/)
- **Distrelec**: CHF 5-7, professional grade - [distrelec.ch](https://www.distrelec.ch/)

**What to Look For**:
- ✅ SPDT (Single Pole Double Throw) - 3 terminals
- ✅ 12mm mounting hole diameter
- ✅ Metal construction (feels premium)
- ✅ ON-ON type (maintained position)

**Alternative**: Illuminated toggle switch - costs CHF 8-12

---

### 4. Battery

| Item | Specs | Qty | Price (CHF) | Suppliers |
|------|-------|-----|-------------|-----------|
| **LiPo Battery** | 3.7V, 2000mAh, JST connector | 1 | CHF 15-25 | Digitec \| Conrad |

**Where to Buy**:
- **Digitec Galaxus**: CHF 18-22, quality batteries with protection - [digitec.ch](https://www.digitec.ch/)
- **Conrad.ch**: CHF 20-25, professional components - [conrad.ch](https://www.conrad.ch/)

**What to Look For**:
- ✅ 2000-2500 mAh capacity
- ✅ JST-PH 2.0mm connector (red/black wires)
- ✅ Protection circuit (PCB on battery)
- ✅ Dimensions fit your enclosure (~50×30×10mm)
- ⚠️ **Buy from reputable seller** - safety matters!

**Safety Note**: LiPo batteries can be dangerous if damaged. Handle with care, don't puncture!

---

### 5. Battery Charger

| Item | Specs | Qty | Price (CHF) | Suppliers |
|------|-------|-----|-------------|-----------|
| **TP4056 Charger Module** | USB-C, 1A charge, protection | 1 | CHF 3-8 | Conrad \| Distrelec |

**Where to Buy**:
- **Conrad.ch**: CHF 6-8, quality modules - [conrad.ch](https://www.conrad.ch/)
- **Distrelec**: CHF 5-7 - [distrelec.ch](https://www.distrelec.ch/)

**What to Look For**:
- ✅ USB-C input (NOT micro-USB)
- ✅ Protection features (DW01A chip visible)
- ✅ Red/Blue indicator LEDs
- ✅ Small form factor (~26×17mm)

---

### 6. Voltage Regulator

| Item | Specs | Qty | Price (CHF) | Suppliers |
|------|-------|-----|-------------|-----------|
| **AMS1117-3.3 Module** | LDO regulator, 3.3V output | 1 | CHF 3-5 | Conrad \| Distrelec |

**Where to Buy**:
- **Conrad.ch**: CHF 3-4 - [conrad.ch](https://www.conrad.ch/)
- **Distrelec**: CHF 4-5 - [distrelec.ch](https://www.distrelec.ch/)

**What to Look For**:
- ✅ 3.3V output
- ✅ 500mA+ current rating
- ✅ Pre-built module (easier than bare IC)
- ✅ Screw terminals or pin headers

---

### 7. USB-C Connector

| Item | Specs | Qty | Price (CHF) | Suppliers |
|------|-------|-----|-------------|-----------|
| **USB-C Panel Mount** | Female, with cable/PCB | 1 | CHF 5-8 | Conrad \| Digitec |

**Where to Buy**:
- **Conrad.ch**: CHF 6-8 - [conrad.ch](https://www.conrad.ch/)
- **Digitec**: CHF 5-7 - [digitec.ch](https://www.digitec.ch/)

**What to Look For**:
- ✅ Female connector (male USB-C cable plugs into it)
- ✅ Mounting holes or nut for panel
- ✅ ~20cm cable attached (easier to wire)
- ✅ Power-only (don't need data pins)

---

## Electronic Components

### Passive Components Kit

| Item | Specs | Qty | Price (CHF) | Suppliers |
|------|-------|-----|-------------|-----------|
| **Capacitor Kit** | 0.1µF, 10µF, 100µF variety | 1 kit | CHF 8-12 | Conrad \| Distrelec |
| **Resistor Kit** | 1/4W, assorted values | 1 kit | CHF 8-12 | Conrad \| Distrelec |

**Where to Buy**:
- **Conrad.ch**: CHF 8-10 per kit, comprehensive assortment - [conrad.ch](https://www.conrad.ch/)
- **Distrelec**: CHF 10-12 per kit, professional grade - [distrelec.ch](https://www.distrelec.ch/)

**Individual Components Needed**:

| Component | Value | Qty | Purpose |
|-----------|-------|-----|---------|
| Electrolytic Capacitor | 100µF, 16V | 2 | Power smoothing |
| Ceramic Capacitor | 10µF, 16V | 2 | Bypass caps |
| Ceramic Capacitor | 0.1µF | 4 | Decoupling |
| Resistor | 10kΩ | 2 | Pull-up |
| Resistor | 330Ω | 1 | LED limiter |
| Diode | 1N4148 | 1 | Reverse protection |

💡 **Tip**: Buy a variety kit if this is your first electronics project. You'll use them in future projects!

**Lausanne Tip**: **Conrad.ch** has a physical store in Geneva (30 min from Lausanne) - you can pick up components same day!

---

## Wiring & Connectors

| Item | Specs | Qty | Price (CHF) | Suppliers |
|------|-------|-----|-------------|-----------|
| **Silicone Wire** | 24 AWG, red+black | 2m each | CHF 8-12 | Conrad \| Distrelec |
| **JST Connectors** | 2-pin, 2.0mm pitch | 5 pairs | CHF 5-8 | Conrad \| Distrelec |
| **Heat Shrink Tubing** | Assorted sizes | 1 kit | CHF 6-10 | Conrad \| Jumbo |
| **Jumper Wires** | Male-to-female, 20cm | 20 | CHF 5-8 | Conrad \| Digitec |

**Where to Buy**:
- **Conrad.ch**: Best selection, CHF 8-12 per item - [conrad.ch](https://www.conrad.ch/)
- **Distrelec**: Professional grade, CHF 10-15 per item - [distrelec.ch](https://www.distrelec.ch/)
- **Local Hardware Stores** (Jumbo, Brico+Loisirs): Basic wire, CHF 5-8

---

## Testing & Prototyping Components

!!! warning "Important for Development"
    These components are essential for testing and prototyping before final assembly. Don't skip these!

### Breadboard & Prototyping

| Item | Specs | Qty | Price (CHF) | Purpose |
|------|-------|-----|-------------|---------|
| **Breadboard** | 400/830 tie points | 1 | CHF 8-12 | Prototyping before soldering |
| **Jumper Wires** | Male-to-male, 10cm | 40 | CHF 5-8 | Breadboard connections |
| **Jumper Wires** | Male-to-female, 20cm | 20 | CHF 5-8 | ESP32 to breadboard |
| **Breadboard Power Supply** | 5V/3.3V module (optional) | 1 | CHF 8-12 | Clean power for testing |

**Where to Buy**:
- **Conrad.ch**: CHF 8-12 breadboard, CHF 5-8 jumper wire sets - [conrad.ch](https://www.conrad.ch/)
- **Digitec**: CHF 10-15 breadboard kits - [digitec.ch](https://www.digitec.ch/)

**Why Needed**: 
- Test all connections before soldering
- Verify firmware works correctly
- Debug issues without desoldering
- See [Breadboard Prototype Guide](../assembly/breadboard.md)

### Extra Components for Testing

| Item | Specs | Qty | Price (CHF) | Purpose |
|------|-------|-----|-------------|---------|
| **Extra Resistors** | 330Ω, 10kΩ | 5 each | CHF 2-3 | Testing LED/data lines |
| **Extra Capacitors** | 100µF, 0.1µF | 5 each | CHF 3-5 | Power supply testing |
| **Extra JST Connectors** | 2-pin, 2.0mm | 3 pairs | CHF 3-5 | Test battery connections |
| **Test Points/Headers** | Male pin headers | 1 strip | CHF 2-3 | Add test points to PCB |

**Why Needed**:
- Components can get damaged during testing
- Need spares for breadboard vs final build
- Allows experimentation without cannibalizing final build

---

## Enclosure

### Option 1: 3D Printed (Recommended)

| Item | Material | Cost (CHF) | Options |
|------|----------|------------|---------|
| **3D Print Service** | PLA filament | CHF 15-25 | [Shapeways](https://www.shapeways.com/) \| [Craftcloud](https://craftcloud3d.com/) |
| **Or Print Yourself** | PLA roll, 1kg | CHF 25-35 | Digitec \| Conrad |

**Files Provided**: STL files in `hardware/enclosure/` directory

**Print Settings**:
- Layer Height: 0.2mm
- Infill: 20%
- Supports: Yes (for overhang areas)
- Material: PLA or PETG

**Lausanne Option**: **FabLab EPFL** - Use their 3D printers for free (with EPFL access) or small membership fee!
- Location: EPFL Campus, Bâtiment MX
- Website: [fablab.epfl.ch](https://fablab.epfl.ch/)
- Cost: Free for students/staff, CHF 50/year for community members

### Option 2: Pre-Made Enclosure

| Item | Specs | Cost (CHF) | Suppliers |
|------|-------|------------|-----------|
| **Project Box** | 100×60×35mm ABS | CHF 8-12 | Conrad \| Distrelec |

**Modifications Needed**:
- Drill holes for toggle switch (12mm)
- Cut slot for USB-C connector
- Cut window for LED strip

**Local Hardware Stores** (Lausanne area):
- **Jumbo** (multiple locations): Basic project boxes, CHF 5-8
- **Brico+Loisirs** (multiple locations): ABS boxes, CHF 8-12

---

## Hardware & Fasteners

| Item | Specs | Qty | Cost (CHF) | Suppliers |
|------|-------|-----|------------|-----------|
| **M3 Screws** | 8mm length | 8 | CHF 2-3 | Conrad/Distrelec |
| **M3 Hex Nuts** | Standard | 8 | CHF 2-3 | Conrad/Distrelec |
| **M3 Standoffs** | 10mm height | 4 | CHF 4-6 | Conrad/Distrelec |
| **Rubber Feet** | Self-adhesive, 10mm | 4 | CHF 3-5 | Conrad/Jumbo |

**Conrad Kit**: CHF 8-12 for complete M3 assortment kit

**Local Option**: **Jumbo** or **Brico+Loisirs** have basic screws/nuts, CHF 2-5

---

## Tools Required

### Essential Tools (Must Have)

| Tool | Approximate Cost (CHF) | Suppliers |
|------|----------------------|-----------|
| **Soldering Iron** | CHF 25-80 | Conrad \| Digitec |
| **Solder** | CHF 8-12 | Conrad \| Jumbo |
| **Wire Strippers** | CHF 12-20 | Conrad \| Jumbo |
| **Screwdriver Set** | CHF 10-15 | Conrad \| Jumbo |
| **Multimeter** | CHF 20-40 | Digitec \| Conrad |
| **USB-C Cable** | CHF 5-10 | Digitec \| Conrad |

**Total Tool Cost**: ~CHF 80-150 (one-time investment, use for many projects!)

**Lausanne Tip**: **FabLab EPFL** has all tools available for free (with EPFL access) or small membership fee!

### Nice to Have (for Testing & Development)

| Tool | Purpose | Cost (CHF) | Suppliers |
|------|---------|------------|-----------|
| **Helping Hands** | Hold PCBs while soldering | CHF 12-18 | Conrad |
| **Hot Glue Gun** | Strain relief, mounting | CHF 10-15 | Jumbo/Brico+Loisirs |
| **Flush Cutters** | Clean wire cuts | CHF 8-12 | Conrad |
| **Tweezers** | Handle small parts | CHF 5-8 | Conrad |
| **Desoldering Pump** | Fix mistakes | CHF 8-12 | Conrad |
| **Solder Wick** | Remove solder | CHF 3-5 | Conrad |
| **Magnifying Glass** | See tiny components | CHF 15-25 | Conrad |
| **Heat Gun** | Heat shrink tubing | CHF 15-30 | Conrad/Jumbo |

---

## Software (Free!)

| Software | Purpose | Links |
|----------|---------|-------|
| **Rust toolchain (rustup)** | Build firmware | [rustup.rs](https://rustup.rs) |
| **espflash** | Flash firmware & monitor serial | [esp-rs/espflash](https://github.com/esp-rs/espflash) |
| **VS Code** | Code editing | [code.visualstudio.com](https://code.visualstudio.com/) |
| **Fusion 360** | 3D design (optional) | [autodesk.com](https://www.autodesk.com/products/fusion-360/personal) |

---

## Complete Shopping List

### Quick Copy-Paste List for Swiss Suppliers

**Core Components**:
```
- ESP32-C3 DevKitM-1 development board
- WS2812B LED strip (1 meter, 60 LEDs)
- 12mm SPDT toggle switch (metal, panel mount)
- 3.7V 2000mAh LiPo battery with JST-PH 2.0mm connector
- TP4056 USB-C charger module (with protection)
- AMS1117-3.3V voltage regulator module
- USB-C panel mount connector (female, with cable)
```

**Components & Wiring**:
```
- Capacitor assortment kit (includes 0.1µF, 10µF, 100µF)
- Resistor assortment kit (includes 330Ω, 10kΩ, etc.)
- 24 AWG silicone wire (red and black, 2m each)
- JST-PH 2.0mm connector kit (male + female pairs)
- Heat shrink tubing assortment
- Male pin headers (for breadboard/ESP32)
```

**Testing & Prototyping**:
```
- Breadboard (400 or 830 tie points)
- Jumper wire kit (male-to-male, male-to-female)
- Extra resistors (330Ω, 10kΩ) - 5 each
- Extra capacitors (100µF, 0.1µF) - 5 each
- Extra JST connectors (3 pairs)
```

**Hardware & Enclosure**:
```
- M3 screw/nut/standoff kit
- Rubber feet (4 pack, self-adhesive)
- Project box (100×60×35mm) OR 3D print enclosure
```

**Tools** (if you don't have):
```
- Soldering iron kit (30W+, temperature controlled)
- Lead-free solder (0.8mm diameter)
- Wire strippers
- Flush cutters
- Multimeter (digital, basic)
- USB-C cable (for programming)
- Screwdriver set (PH0/PH1)
```

---

## Swiss Suppliers Directory

### Primary Suppliers (Recommended)

#### Digitec Galaxus
- **Website**: [digitec.ch](https://www.digitec.ch/)
- **Delivery**: 1-2 days (free over CHF 50)
- **Strengths**: ESP32 boards, LED strips, batteries, tools
- **Best For**: Fast delivery, good prices, Swiss customer service

#### Conrad.ch
- **Website**: [conrad.ch](https://www.conrad.ch/)
- **Delivery**: 2-3 days (free over CHF 50)
- **Strengths**: Complete electronics catalog, passive components, tools
- **Physical Store**: Geneva (30 min from Lausanne) - [Store Finder](https://www.conrad.ch/fr/ch/pages/store-finder)
- **Best For**: One-stop shopping, professional components

#### Distrelec
- **Website**: [distrelec.ch](https://www.distrelec.ch/)
- **Delivery**: 1-2 days (free over CHF 50)
- **Strengths**: Professional components, industrial grade
- **Best For**: Quality components, technical support

### Local Stores (Lausanne Area)

#### Play Zone (Lausanne)
- **Location**: Centre Flon, Lausanne
- **Website**: [playzone.ch](https://www.playzone.ch/)
- **Specialty**: Arduino kits, ESP32 boards, maker components
- **Best For**: In-person shopping, immediate pickup

#### Jumbo (Multiple Locations)
- **Locations**: Multiple in Lausanne area
- **Website**: [jumbo.ch](https://www.jumbo.ch/)
- **Specialty**: Basic tools, wire, basic components
- **Best For**: Basic tools, wire, screws

#### Brico+Loisirs (Multiple Locations)
- **Locations**: Multiple in Lausanne area
- **Website**: [bricorama.ch](https://www.bricorama.ch/)
- **Specialty**: Tools, hardware, basic electronics
- **Best For**: Tools, project boxes, hardware

### Maker Spaces (Lausanne Area)

#### FabLab EPFL
- **Location**: EPFL Campus, Bâtiment MX
- **Website**: [fablab.epfl.ch](https://fablab.epfl.ch/)
- **Tools**: 3D printers, soldering stations, laser cutters, milling machines
- **Access**: Free for EPFL students/staff, CHF 50/year for community members
- **Best For**: 3D printing enclosure, using tools, getting help

#### Makerspace Renens
- **Location**: Renens (15 min from Lausanne)
- **Tools**: Full workshop access
- **Community**: Meetups and workshops
- **Best For**: Community support, workshops

### European Suppliers (Optional)

#### Reichelt (Germany)
- **Website**: [reichelt.com](https://www.reichelt.com/)
- **Shipping**: CHF 9, free over CHF 80
- **Delivery**: 2-3 days (no customs within EU)
- **Best For**: Complete electronics, good prices

---

## Swiss Customs & Tax Information

!!! info "Import Rules for Switzerland"
    - **Tax-free limit**: CHF 62 (including shipping)
    - **VAT rate**: 7.7% on (value + shipping)
    - **Processing fee**: CHF 11.50-18.00 (Swiss Post)
    - **Customs declaration**: Required for all imports
    - **Pro tip**: Order from Swiss/EU suppliers to avoid customs entirely

**Example calculation for CHF 80 order from outside EU**:
```
Order value:        CHF 80.00
Shipping:          CHF 10.00
Subtotal:          CHF 90.00
VAT (7.7%):        CHF  6.93
Processing fee:    CHF 18.00
──────────────────────────
TOTAL:             CHF 114.93
```

**Strategy**: 
- Use Swiss/EU suppliers (Digitec, Conrad, Distrelec, Reichelt) - no customs
- Keep individual orders under CHF 62 if ordering from outside EU
- Split orders to minimize customs fees

---

## Cost Breakdown - Switzerland

### Option 1: Fast Build (Swiss Suppliers)

| Component | Quantity | Price (CHF) | Supplier |
|-----------|----------|-------------|----------|
| ESP32-C3 DevKitM-1 | 1 | CHF 15 | Digitec |
| WS2812B LED Strip (1m) | 1 | CHF 12 | Digitec |
| SPDT Toggle Switch | 1 | CHF 7 | Conrad |
| LiPo Battery 2000mAh | 1 | CHF 20 | Digitec |
| TP4056 Charger Module | 1 | CHF 7 | Conrad |
| AMS1117 Regulator Module | 1 | CHF 4 | Conrad |
| USB-C Panel Connector | 1 | CHF 7 | Conrad |
| Capacitor Kit | 1 | CHF 9 | Conrad |
| Resistor Kit | 1 | CHF 9 | Conrad |
| Wire Kit | 1 | CHF 10 | Conrad |
| JST Connectors | 5 pairs | CHF 6 | Conrad |
| Heat Shrink Tubing | 1 kit | CHF 7 | Conrad |
| Breadboard | 1 | CHF 10 | Conrad |
| Jumper Wires | 1 kit | CHF 6 | Conrad |
| Extra Components | 1 set | CHF 5 | Conrad |
| M3 Hardware Kit | 1 | CHF 9 | Conrad |
| Rubber Feet | 4 | CHF 4 | Conrad |
| Project Box | 1 | CHF 10 | Conrad |
| **Subtotal** | | **CHF 156** | |
| Shipping | | CHF 0 | (Free over CHF 50) |
| **TOTAL** | | **CHF 156** | |
| **Delivery** | | **1-3 days** | |

### Option 2: Budget Build (Outside EU)

| Component | Quantity | Price (CHF) | Supplier |
|-----------|----------|-------------|----------|
| ESP32-C3 DevKitM-1 | 1 | CHF 5 | China |
| WS2812B LED Strip (1m) | 1 | CHF 2 | China |
| SPDT Toggle Switch | 1 | CHF 1 | China |
| LiPo Battery 2000mAh | 1 | CHF 8 | China |
| TP4056 Charger Module | 1 | CHF 2 | China |
| AMS1117 Regulator Module | 1 | CHF 1 | China |
| USB-C Panel Connector | 1 | CHF 2 | China |
| Component Kit | 1 | CHF 4 | China |
| Wire & Connectors Kit | 1 | CHF 5 | China |
| Breadboard | 1 | CHF 3 | China |
| Jumper Wires | 1 kit | CHF 2 | China |
| Extra Components | 1 set | CHF 2 | China |
| M3 Hardware Kit | 1 | CHF 3 | China |
| Project Box | 1 | CHF 5 | China |
| **Subtotal** | | **CHF 45** | |
| Shipping | | CHF 0 | (Free shipping) |
| Customs/VAT (if >CHF 62) | | CHF 0-8 | (Stay under CHF 62) |
| **TOTAL** | | **CHF 45-53** | |
| **Delivery** | | **3-4 weeks** | |

---

## Estimated Delivery Times

| Source | Delivery Time | Shipping Cost | Customs | Total Time |
|--------|--------------|---------------|---------|------------|
| **Digitec/Conrad** | 1-3 days | Free over CHF 50 | None | 1-3 days |
| **Distrelec** | 1-2 days | Free over CHF 50 | None | 1-2 days |
| **Reichelt (Germany)** | 2-3 days | CHF 9 (free >CHF 80) | None | 2-3 days |
| **Outside EU** | 15-30 days | Free | CHF 0-18 | 3-4 weeks |
| **Local Store** | Same day | - | None | Same day |

💡 **Pro Tip**: Order critical components (ESP32, battery) from Swiss suppliers for fast delivery, order passive components from cheaper sources to save money!

---

## Next Steps

1. ✅ Copy the shopping list above
2. 🛒 Order components:
   - **Fast**: Digitec + Conrad (CHF 90-100, 1-3 days)
   - **Budget**: Outside EU suppliers (CHF 45-50, 3-4 weeks)
3. ⏰ While waiting, read the [Assembly Guide](../assembly/soldering.md)
4. 💻 Set up development environment (see [Firmware Installation](../../docs/FIRMWARE_INSTALLATION.md))
5. 🎨 Design or print the enclosure (or use FabLab EPFL!)
6. ☕ Relax - you're about to build something awesome!

---

## Testing Checklist

Before final assembly, verify all components work:

- [ ] ESP32-C3 boots and connects to WiFi
- [ ] Battery charges correctly (LED indicators work)
- [ ] Button press detected reliably
- [ ] All 8 LEDs light up correctly
- [ ] API calls succeed
- [ ] Deep sleep mode works
- [ ] Battery lasts expected time
- [ ] USB-C charging works through panel connector

See [Component Testing Guide](../assembly/testing.md) for detailed testing procedures.

---

**Questions about components?** Check the [FAQ](../../docs/FAQ.md) or open an issue!

**Found better prices?** Submit a PR to update this list!

**Need help in Lausanne?** Visit FabLab EPFL or join Makerspace Renens!
