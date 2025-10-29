# Bill of Materials

Complete shopping list for building the Wall Clock In Machine.

!!! tip "Shopping Strategy"
    - **Order from AliExpress** for lowest cost (2-4 week shipping)
    - **Order from Amazon** for fast delivery (2-day shipping)
    - **Order from Adafruit/SparkFun** for guaranteed quality
    - **Buy multiples** - save on shipping and have spares!

## Quick Summary

| Category | Items | Total Cost |
|----------|-------|------------|
| Electronics | 6 components | $18 |
| Power | 3 components | $11 |
| Enclosure | Case + hardware | $6 |
| Total | | **$35** |

**Time to Assemble**: 2-3 hours for first build

## Core Electronics

### 1. Microcontroller

**ESP32-C3-DevKitM-1** (or compatible)

- Quantity: 1
- Price: $4-6
- Features: WiFi, Bluetooth, USB-C, 22 GPIO
- Specifications:
    - CPU: RISC-V @ 160MHz
    - RAM: 400KB SRAM
    - Flash: 4MB
    - Connector: USB-C

**Where to Buy**:

| Vendor | Link | Price | Shipping |
|--------|------|-------|----------|
| **AliExpress** | [Search ESP32-C3](https://www.aliexpress.com/w/wholesale-esp32-c3-devkit.html) | $3.50 | Free (3-4 weeks) |
| **Amazon** | [Amazon Search](https://www.amazon.com/s?k=esp32-c3) | $6.99 | Prime 2-day |
| **Espressif** | [Official Store](https://www.espressif.com/en/products/devkits) | $5.95 | Varies |
| **Adafruit** | [Product #5337](https://www.adafruit.com/product/5337) | $9.95 | $5 flat |

!!! note "Compatible Boards"
    Any ESP32-C3 board works! Look for:
    - ESP32-C3-DevKitC-02
    - ESP32-C3-WROOM-02
    - ESP32-C3 Super Mini
    
    Just verify it has: USB-C port, 4MB flash, accessible GPIO pins

### 2. LED Strip

**WS2812B Addressable RGB LED Strip** (8 LEDs minimum)

- Quantity: 8 LEDs (or buy 1 meter strip with 60 LEDs)
- Price: $2-5
- Specifications:
    - Voltage: 5V DC
    - Type: WS2812B / SK6812 / NeoPixel
    - Individual addressable RGB
    - Current: ~60mA per LED at full brightness

**Where to Buy**:

| Vendor | Link | Price | Notes |
|--------|------|-------|-------|
| **AliExpress** | [WS2812B Strip](https://www.aliexpress.com/w/wholesale-ws2812b.html) | $2/meter | Buy 1 meter, cut to size |
| **Amazon** | [Amazon WS2812B](https://www.amazon.com/s?k=ws2812b+led+strip) | $8/meter | Pre-cut options available |
| **Adafruit** | [NeoPixel Strip](https://www.adafruit.com/product/1138) | $10/meter | High quality, weatherproof |
| **BTF-Lighting** | [Amazon Store](https://www.amazon.com/stores/BTF-LIGHTING/page/80C2E92D-D672-4FD0-AD3D-2B8D85F0AA08) | $9/meter | Popular brand |

!!! tip "LED Options"
    - **60 LEDs/meter**: Easy to cut, standard density
    - **144 LEDs/meter**: More compact, harder to cut
    - **Pre-wired**: Look for "WS2812B 8 LED" modules
    - **Compatible**: SK6812, NeoPixel, any WS2812 variant works

### 3. Toggle Switch

**SPDT Toggle Switch** (ON-OFF-ON or ON-ON)

- Quantity: 1
- Price: $1-3
- Specifications:
    - Type: Single Pole Double Throw (SPDT)
    - Rating: 3A @ 125VAC
    - Mounting: Panel mount (6mm thread)
    - Actuation: Toggle/Lever

**Where to Buy**:

| Vendor | Link | Price |
|--------|------|-------|
| **AliExpress** | [SPDT Toggle](https://www.aliexpress.com/w/wholesale-spdt-toggle-switch.html) | $0.50 |
| **Amazon** | [E-Switch 100DP1T1B1M2QEH](https://www.amazon.com/s?k=spdt+toggle+switch+panel) | $3.00 |
| **Adafruit** | [Toggle Switch](https://www.adafruit.com/product/3220) | $0.95 |
| **Mouser** | [C&K 7101](https://www.mouser.com/c/electromechanical/switches/toggle-switches/) | $2.50 |

!!! warning "Switch Type"
    - ✅ **SPDT** (Single Pole Double Throw) - Has 3 terminals
    - ✅ **ON-ON** - Two stable positions
    - ❌ **SPST** - Only 2 terminals (won't work)
    - ❌ **Momentary** - Returns to center (not suitable)

### 4. Resistor (for LEDs)

**330Ω Resistor** (1/4W)

- Quantity: 1
- Price: $0.10 (or buy pack of 100)
- Specifications:
    - Value: 330Ω (orange-orange-brown)
    - Wattage: 1/4W or higher
    - Tolerance: 5% or better

**Where to Buy**:

| Vendor | Link | Price |
|--------|------|-------|
| **AliExpress** | [Resistor Kit](https://www.aliexpress.com/w/wholesale-resistor-kit.html) | $2 for 1000pcs |
| **Amazon** | [Elegoo Resistor Kit](https://www.amazon.com/ELEGOO-Resistor-Assortment-Projects-Breadboard/dp/B07C7DFDN8) | $8 for 1200pcs |
| **Adafruit** | [Single Resistor](https://www.adafruit.com/product/2781) | $0.75 |

!!! tip "Alternative"
    Many WS2812B strips don't need external resistors. Try without first!

### 5. Capacitor (for LEDs)

**1000µF Electrolytic Capacitor** (6.3V or higher)

- Quantity: 1
- Price: $0.20
- Specifications:
    - Capacitance: 470µF - 1000µF
    - Voltage: 6.3V minimum (16V recommended)
    - Type: Electrolytic

**Where to Buy**:

| Vendor | Link | Price |
|--------|------|-------|
| **AliExpress** | [Capacitor Kit](https://www.aliexpress.com/w/wholesale-electrolytic-capacitor-kit.html) | $3 for 120pcs |
| **Amazon** | [Assorted Kit](https://www.amazon.com/s?k=electrolytic+capacitor+assortment) | $10 for 500pcs |
| **Adafruit** | [1000µF 25V](https://www.adafruit.com/product/2193) | $0.95 |

!!! note "Optional Component"
    The capacitor smooths power to the LEDs and prevents flickering. Not strictly required for 8 LEDs.

### 6. Wires & Connectors

**Hookup Wire** (22-26 AWG)

- Quantity: 1 meter of each color (red, black, yellow/white)
- Price: $3-5 for assorted spool
- Specifications:
    - Gauge: 22-26 AWG solid or stranded
    - Colors: Red (power), Black (ground), Other (data)

**JST-PH 2.0 Connectors** (Optional but recommended)

- Quantity: 2-3 sets (male + female)
- Price: $2-4 for 10 pairs
- Use: Battery connection, easy disconnection

**Where to Buy**:

| Vendor | Link | Price |
|--------|------|-------|
| **AliExpress** | [Wire Kit + JST](https://www.aliexpress.com/w/wholesale-hookup-wire-kit.html) | $5 |
| **Amazon** | [Striveday Wire Kit](https://www.amazon.com/Electrical-Striveday-Stranded-Different-Breadboard/dp/B07T4SYVYH) | $14 |
| **Adafruit** | [Silicone Wire Spool](https://www.adafruit.com/product/2051) | $3/spool |

## Power Components

### 7. LiPo Battery

**3.7V 2000mAh Lithium Polymer Battery** (503450 size)

- Quantity: 1
- Price: $7-10
- Specifications:
    - Voltage: 3.7V nominal (4.2V max, 3.0V min)
    - Capacity: 2000mAh (higher OK, longer runtime)
    - Size: 50×34×5mm (503450) - flexible
    - Connector: JST-PH 2.0 (2-pin)
    - Protection: Built-in PCM (Protection Circuit Module)

**Where to Buy**:

| Vendor | Link | Price | Notes |
|--------|------|-------|-------|
| **AliExpress** | [LiPo 2000mAh](https://www.aliexpress.com/w/wholesale-lipo-battery-2000mah-3.7v.html) | $6-8 | Check size fits |
| **Amazon** | [Adafruit LiPo](https://www.amazon.com/stores/Adafruit/page/6F1C5E2B-9B57-4F5A-9C4D-1C3F5F3E5A5D) | $10-12 | High quality |
| **Adafruit** | [2000mAh Battery](https://www.adafruit.com/product/2011) | $9.95 | With JST connector |

!!! danger "Battery Safety"
    - ⚠️ **Do not puncture or short circuit**
    - ⚠️ **Do not charge unattended**
    - ⚠️ **Store in cool, dry place**
    - ⚠️ **Dispose properly** (battery recycling)
    - ✅ **Use batteries with built-in protection circuit**

!!! tip "Size Flexibility"
    Any 3.7V LiPo from 1000mAh to 3000mAh works:
    - **1000mAh**: Smaller, lighter, 5-7 day runtime
    - **2000mAh**: Recommended, 10-14 day runtime
    - **3000mAh**: Larger, heavier, 15-20 day runtime

### 8. Battery Charger

**TP4056 Lithium Battery Charger Module** (with protection)

- Quantity: 1
- Price: $1-3
- Specifications:
    - Input: Micro-USB or USB-C (5V)
    - Output: 4.2V (LiPo charging)
    - Current: 1A max (adjustable with resistor)
    - Protection: Overcharge, overdischarge, overcurrent
    - Indicators: Red LED (charging), Blue LED (full)

**Where to Buy**:

| Vendor | Link | Price |
|--------|------|-------|
| **AliExpress** | [TP4056 USB-C](https://www.aliexpress.com/w/wholesale-tp4056-usb-c.html) | $1.50 |
| **Amazon** | [HiLetgo TP4056](https://www.amazon.com/s?k=tp4056+charger+module) | $8 for 5-pack |
| **Adafruit** | [USB LiPo Charger](https://www.adafruit.com/product/1304) | $7.50 |

!!! note "USB Type"
    - **USB-C version**: Recommended (same as ESP32-C3)
    - **Micro-USB version**: Works but need 2 different cables

### 9. Voltage Regulator

**AMS1117-3.3V Linear Regulator Module**

- Quantity: 1
- Price: $1-2
- Specifications:
    - Input: 4.5V - 7V (or 3.3-6V for LDO version)
    - Output: 3.3V @ 800mA
    - Type: Linear LDO (Low Dropout)
    - Package: SOT-223 or module with caps

**Where to Buy**:

| Vendor | Link | Price |
|--------|------|-------|
| **AliExpress** | [AMS1117 Module](https://www.aliexpress.com/w/wholesale-ams1117-3.3v-module.html) | $1 |
| **Amazon** | [HiLetgo AMS1117](https://www.amazon.com/s?k=ams1117+3.3v+module) | $7 for 10-pack |
| **Adafruit** | [Breadboard Regulator](https://www.adafruit.com/product/2165) | $1.95 |

!!! tip "Alternative"
    Many ESP32-C3 boards have built-in 3.3V regulation from 5V USB. If yours does, you can power LEDs from 5V USB and skip this component for USB-only operation.

## Enclosure & Hardware

### 10. Enclosure

**3D Printed Case** or **Laser-Cut Acrylic Box**

- Quantity: 1
- Price: $5-10 (materials) or $15-25 (printed/cut)
- Specifications:
    - Dimensions: 100×60×35mm (internal)
    - Material: PLA, PETG, or 3mm acrylic
    - Features: LED window, switch hole, USB access

**Options**:

| Option | Cost | Time | Notes |
|--------|------|------|-------|
| **3D Print Yourself** | $3 | 6 hours | Need 3D printer |
| **Print Service** | $15-25 | 3-5 days | Use Shapeways, Craftcloud |
| **Laser Cut Service** | $20-30 | 3-5 days | Use Ponoko, SendCutSend |
| **DIY Wood/Plastic** | $5 | 2 hours | Hand tools + plastic box |

**Print Services**:

- [Craftcloud](https://craftcloud3d.com/) - Compare prices from 100+ services
- [Shapeways](https://www.shapeways.com/) - Professional finish
- [3D Hubs](https://www.hubs.com/) - Local 3D printing

**Laser Cut Services**:

- [Ponoko](https://www.ponoko.com/) - Upload SVG/DXF files
- [SendCutSend](https://sendcutsend.com/) - Metal and plastic

**DIY Enclosure Ideas**:

1. **Plastic Project Box** ($5 from Amazon/eBay)
2. **Hammond 1591 Enclosure** ($8 from Mouser)
3. **Mint Tin** (free! - Altoids tin)
4. **Wooden Box** (craft store - $3-5)

**3D Model Files**: Available in `/hardware/enclosure/` folder (STL files)

### 11. Mounting Hardware

**Screws, Standoffs, Nuts**

- Quantity: Various
- Price: $3-5
- Specifications:
    - M3 screws (8-10mm length) × 4
    - M3 hex standoffs (10mm) × 4
    - M2 screws (6mm) for ESP32 × 2

**Where to Buy**:

| Vendor | Link | Price |
|--------|------|-------|
| **AliExpress** | [M3 Standoff Kit](https://www.aliexpress.com/w/wholesale-m3-standoff-kit.html) | $3 |
| **Amazon** | [Sutemribor 1080pcs Kit](https://www.amazon.com/Sutemribor-1080PCS-Standoff-Assortment-Male-Female/dp/B07D7828LC) | $16 |
| **Home Depot** | Loose screws | $2 |

## Optional Components

### For Enhanced Features

| Component | Purpose | Price | Link |
|-----------|---------|-------|------|
| **Buzzer** | Audio feedback | $1 | [AliExpress](https://www.aliexpress.com/w/wholesale-passive-buzzer-5v.html) |
| **OLED Display** | Show time/status | $5 | [Amazon I2C OLED](https://www.amazon.com/s?k=0.96+oled+i2c) |
| **DHT22 Sensor** | Temperature/humidity | $3 | [Adafruit DHT22](https://www.adafruit.com/product/385) |
| **Button** | Extra input | $0.20 | [Tactile Button](https://www.adafruit.com/product/367) |
| **NFC Reader** | RFID for multi-user | $8 | [PN532 Module](https://www.amazon.com/s?k=pn532+nfc) |

## Tools Required

!!! info "You'll Need These Tools"
    Not included in cost above - these are workshop tools you may already have:

### Essential Tools

| Tool | Purpose | Price | Where |
|------|---------|-------|-------|
| **Soldering Iron** | Solder components | $15-50 | [Amazon](https://www.amazon.com/s?k=soldering+iron+kit) |
| **Solder** | Join connections | $5 | [60/40 Rosin Core](https://www.amazon.com/s?k=rosin+core+solder) |
| **Wire Strippers** | Strip wire insulation | $8 | Hardware store |
| **Flush Cutters** | Cut wires/leads | $7 | [Amazon](https://www.amazon.com/s?k=flush+cutters) |
| **Multimeter** | Test voltage/continuity | $12 | [Amazon](https://www.amazon.com/s?k=digital+multimeter) |
| **USB-C Cable** | Program ESP32 | $5 | Any USB-C cable |

**Total Tool Cost**: ~$50-100 (one-time investment, reusable for all projects)

### Nice to Have

- **Third Hand/Helping Hands** - Hold components while soldering ($10)
- **Heat Shrink Tubing** - Insulate connections ($5)
- **Hot Glue Gun** - Secure components ($8)
- **Drill + Bits** - Make holes in enclosure ($30)
- **Label Maker** - Mark connections ($15)

## Shopping Lists

### Budget Option (~$35 total)

Perfect for first build:

1. ESP32-C3 from AliExpress: $3.50
2. WS2812B LED Strip (1 meter): $2.00
3. SPDT Toggle Switch: $0.50
4. 2000mAh LiPo Battery: $7.00
5. TP4056 Charger (USB-C): $1.50
6. AMS1117 Regulator Module: $1.00
7. Wire Kit + Connectors: $5.00
8. Resistor/Capacitor Kit: $3.00
9. Plastic Project Box: $5.00
10. M3 Hardware Kit: $3.00
11. USB-C Cable: $3.00

**Subtotal**: $34.50  
**Shipping**: Free (3-4 weeks from China)

### Premium Option (~$80 total)

Higher quality, faster shipping:

1. ESP32-C3 from Adafruit: $9.95
2. NeoPixel Strip from Adafruit: $10.00
3. Quality Toggle Switch: $3.00
4. Adafruit 2000mAh LiPo: $9.95
5. Adafruit USB LiPo Charger: $7.50
6. Regulator Module from Amazon: $2.00
7. Premium Wire Kit: $14.00
8. Component Kits: $10.00
9. 3D Printed Enclosure: $20.00
10. Hardware Assortment: $10.00
11. USB-C Cable: $5.00

**Subtotal**: $101.40  
**Shipping**: ~$10 (2-3 days domestic)

### Bulk Order (Build 5 units)

Save on per-unit cost:

- ESP32-C3 × 5: $17.50 ($3.50 each)
- LED Strips × 5m: $10 ($2 each)
- Switches × 10: $5 ($0.50 each)
- Batteries × 5: $35 ($7 each)
- Chargers × 5: $7.50 ($1.50 each)
- Regulators × 10: $10 ($1 each)
- Shared wire/component kits: $15
- Project boxes × 5: $25 ($5 each)
- Shared hardware: $10

**Total**: $135 for 5 units = **$27 per unit**  
**Savings**: 25% vs buying individually

## Where to Get Everything

### 🇨🇭 Local Shopping in Lausanne, Switzerland

**Physical Stores in Lausanne Area**:

| Store | Location | Speciality | Website |
|-------|----------|------------|---------|
| **Digitec Galaxus** | Online + Zürich | Electronics, fast delivery | [digitec.ch](https://www.digitec.ch/) |
| **Play Zone** | Centre Flon, Lausanne | Electronics, Arduino kits | [playzone.ch](https://www.playzone.ch/) |
| **Distrelec** | Online + pickup points | Professional components | [distrelec.ch](https://www.distrelec.ch/) |
| **Brack** | Online, 1-2 day delivery | Consumer electronics | [brack.ch](https://www.brack.ch/) |

**Maker Spaces in Lausanne** (borrow tools, get help):

- **FabLab EPFL** - [fablab.epfl.ch](https://fablab.epfl.ch/)
  - Location: EPFL Campus, Bâtiment MX
  - Tools: 3D printers, soldering stations, laser cutters
  - Open hours: Check website for schedule
  - Perfect for: Students with EPFL access

- **Makerspace Renens** - Near Lausanne
  - Location: Renens (15 min from Lausanne)
  - Tools: Full workshop access
  - Community: Meetups and workshops

### European Suppliers (Fast Shipping to Switzerland)

**Germany** (2-3 day delivery):

| Vendor | Speciality | Shipping | Website |
|--------|------------|----------|---------|
| **Reichelt** | Complete electronics | CHF 9, free >CHF 80 | [reichelt.com](https://www.reichelt.com/) |
| **Conrad Electronic** | Professional components | CHF 8, free >CHF 50 | [conrad.ch](https://www.conrad.ch/) |
| **Berrybase** | Raspberry Pi & ESP32 | CHF 10 | [berrybase.de](https://www.berrybase.de/) |
| **Eckstein** | Arduino & makers | CHF 7 | [eckstein-shop.de](https://www.eckstein-shop.de/) |

**France** (2-4 day delivery):

| Vendor | Speciality | Shipping | Website |
|--------|------------|----------|---------|
| **Kubii** | Maker components | CHF 12 | [kubii.fr](https://www.kubii.fr/) |
| **GoTronic** | Electronics kits | CHF 10 | [gotronic.fr](https://www.gotronic.fr/) |

**UK** (3-5 days, customs possible):

| Vendor | Speciality | Shipping | Website |
|--------|------------|----------|---------|
| **Pimoroni** | Quality maker products | £10-15 + customs | [pimoroni.com](https://shop.pimoroni.com/) |
| **The Pi Hut** | Raspberry Pi ecosystem | £8-12 + customs | [thepihut.com](https://thepihut.com/) |

!!! warning "Brexit & Customs"
    Orders from UK may incur:
    - Import VAT (7.7% in Switzerland)
    - Customs clearance fee (CHF 11-18)
    - Consider ordering from EU instead

### Budget Options

**AliExpress** (cheapest, 3-4 weeks):

- Search: "ESP32-C3 kit"
- Order from seller with good ratings (>95%)
- Price: CHF 25-35 with free shipping
- **Swiss customs**: Orders >CHF 62 incur VAT + CHF 18 processing
- Best for: Budget builds, patient buyers

**Bangood** (alternative to AliExpress):

- Similar prices and shipping times
- Sometimes better shipping to Switzerland
- Price: CHF 30-40 including shipping

### Recommended Shopping Plan for Lausanne

**Option 1: Fast Build (2-3 days, CHF 90)**

1. **Digitec Galaxus** (order online, delivered to Lausanne):
   - ESP32-C3 DevKit: CHF 15
   - WS2812B LED Strip (1m): CHF 12
   - LiPo Battery 2000mAh: CHF 18
   - USB-C cables and connectors: CHF 10
   - Shipping: Free over CHF 50

2. **Conrad.ch** (online or store in Geneva):
   - TP4056 Charger Module: CHF 8
   - AMS1117 Regulator: CHF 3
   - Toggle Switch: CHF 5
   - Wire kit: CHF 12
   - Resistor/Capacitor kit: CHF 8
   - Shipping: Free over CHF 50

3. **FabLab EPFL** or local hardware store:
   - Enclosure materials: CHF 8-15
   - Screws/standoffs: CHF 5

**Total: ~CHF 90-100** (Available in 2-3 days)

**Option 2: Budget Build (3-4 weeks, CHF 40)**

1. **AliExpress** (single order to avoid multiple customs):
   - ESP32-C3 kit with LEDs: CHF 15
   - 2000mAh LiPo + TP4056 charger: CHF 10
   - Complete component kit: CHF 8
   - Project box: CHF 5
   - Shipping: Free

2. **Local hardware store** (Landi, Jumbo):
   - Screws/standoffs: CHF 3-5

**Total: ~CHF 40-45** (Wait 3-4 weeks)

**Option 3: Premium Build (1-2 days, CHF 150)**

Visit **FabLab EPFL** + **Digitec**:
- All components from Swiss suppliers
- Professional quality parts
- Workshop access for assembly
- Community support

**Total: ~CHF 150** (Same/next day)

### Price Comparison (in CHF)

| Component | AliExpress | Digitec/Conrad | Adafruit (import) |
|-----------|-----------|----------------|-------------------|
| ESP32-C3 | CHF 4 | CHF 15 | CHF 18 |
| LED Strip | CHF 2 | CHF 12 | CHF 20 |
| LiPo Battery | CHF 7 | CHF 18 | CHF 25 |
| Charger | CHF 2 | CHF 8 | CHF 15 |
| Other parts | CHF 10 | CHF 25 | CHF 30 |
| **Subtotal** | **CHF 25** | **CHF 78** | **CHF 108** |
| Shipping | Free (slow) | CHF 0-12 | CHF 20-30 |
| Customs/VAT | CHF 0-5 | CHF 0 | CHF 18-25 |
| **TOTAL** | **CHF 25-30** | **CHF 78-90** | **CHF 146-163** |
| **Delivery** | **3-4 weeks** | **1-3 days** | **1-2 weeks** |

### Swiss Tax & Customs Information

!!! info "Import Rules"
    - **Tax-free limit**: CHF 62 (including shipping)
    - **VAT rate**: 7.7% on (value + shipping)
    - **Processing fee**: CHF 11.50-18.00 (Swiss Post)
    - **Customs declaration**: Required for all imports
    - **Pro tip**: Split orders to stay under CHF 62

**Example calculation for CHF 80 order**:
```
Order value:        CHF 80.00
Shipping:          CHF 10.00
Subtotal:          CHF 90.00
VAT (7.7%):        CHF  6.93
Processing fee:    CHF 18.00
──────────────────────────
TOTAL:             CHF 114.93
```

### Regional Options (Other Countries)

**Other Europe**:
- [Pimoroni](https://shop.pimoroni.com/) (UK) - Quality products, Brexit customs
- [Mouser](https://www.mouser.ch/) (Switzerland) - Professional components
- [Farnell](https://ch.farnell.com/) (Switzerland) - Industrial supplier

**Asia**:
- [Taobao](https://www.taobao.com/) (China - cheapest!)
- [Tokopedia](https://www.tokopedia.com/) (Indonesia)
- [Lazada](https://www.lazada.com/) (Southeast Asia)

**Australia**:
- [Core Electronics](https://core-electronics.com.au/)
- [Little Bird Electronics](https://littlebirdelectronics.com.au/)

**Americas**:
- [Adafruit](https://www.adafruit.com/) (USA) - High shipping + customs
- [SparkFun](https://www.sparkfun.com/) (USA) - High shipping + customs
- [Amazon.de](https://www.amazon.de/) (Germany) - Ships to Switzerland

## Next Steps

**Got your parts?** Great! Continue to:

- [**Hardware Specifications**](specifications.md) - Detailed technical specs
- [**Enclosure Design**](enclosure.md) - Build the box
- [**Assembly Guide**](../assembly/soldering.md) - Start building!

**Questions about components?**

- Check [Troubleshooting - Hardware Issues](../troubleshooting/hardware.md)
- Ask in [GitHub Discussions](https://github.com/yourusername/wallClockInMachine/discussions)
