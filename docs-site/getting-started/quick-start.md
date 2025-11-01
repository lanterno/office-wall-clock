# Quick Start Guide

Get your Wall Clock In Machine up and running in under 2 hours! This guide assumes you have all components ready.

## 🇨🇭 For Lausanne Residents

**Fastest path to success**:

1. **Order components**: CHF 90, 2-3 day delivery
   - [Digitec Galaxus](https://www.digitec.ch/) - Electronics
   - [Conrad.ch](https://www.conrad.ch/) - Components

2. **Get tools**: Free at FabLab EPFL or CHF 80 one-time
   - **FabLab EPFL**: Bâtiment MX, EPFL Campus
   - Open hours: Check [fablab.epfl.ch](https://fablab.epfl.ch/)

3. **Build time**: 2-3 hours at FabLab (help available!)

## Timeline Overview

```
Week 1: Order & Wait
┌────────────────────────┐
│ Day 1: Order parts     │ 30 min
│ Day 2-3: Wait          │ ⏳
│ Day 3: Parts arrive! ✓ │
└────────────────────────┘

Week 2: Build
┌────────────────────────┐
│ Hour 1: Solder         │ 🔥
│ Hour 2: Assemble       │ 🔧
│ Hour 3: Program        │ 💻
│ Done! Working device ✓ │
└────────────────────────┘
```

**Total active time**: ~3 hours  
**Total calendar time**: 3-4 days (with fast shipping)

## Step-by-Step: The Express Route

### Step 1: Order Components (30 minutes)

**Shopping List** (CHF 90 total):

**From Digitec Galaxus**:
- [ ] ESP32-C3 DevKit (~CHF 15)
- [ ] WS2812B LED Strip 1m (~CHF 12)
- [ ] 2000mAh LiPo Battery (~CHF 18)
- [ ] USB-C cable (~CHF 5)

**Search terms**: "ESP32-C3", "WS2812B LED", "LiPo battery 2000mah"

**From Conrad.ch**:
- [ ] TP4056 Charger Module (~CHF 8)
- [ ] AMS1117 3.3V Regulator (~CHF 3)
- [ ] SPDT Toggle Switch (~CHF 5)
- [ ] Wire kit 22AWG (~CHF 12)
- [ ] Component kit (resistors, caps) (~CHF 8)
- [ ] Project box or 3D print material (~CHF 10)

**Delivery**: 1-3 days to Lausanne

!!! tip "Student Discount"
    EPFL students: Check if you have access to components through your lab or FabLab!

### Step 2: Prepare (15 minutes)

While waiting for parts:

1. **Download firmware**:
   ```bash
   git clone https://github.com/yourusername/wallClockInMachine.git
   cd wallClockInMachine/firmware
   ```

2. **Install Rust toolchain and espflash**:
   ```fish
   curl -fsSL https://sh.rustup.rs | sh
   rustup target add riscv32imc-unknown-none-elf
   cargo install espflash --locked
   ```
   rustup target add riscv32imc-esp-espidf
   cargo install espflash --locked
   ```

3. **Configure API endpoint**:
   Edit `firmware/src/config.rs`:
   ```rust
   pub const API_ENDPOINT: &str = "https://your-api.com";
   pub const API_TOKEN: &str = "your_token_here";
   ```

4. **Read assembly guide** (you are here!)

### Step 3: Solder Components (60-90 minutes)

**Location**: FabLab EPFL or home workshop

**Tools needed**: All available at FabLab

**Process**:

1. ☑️ **Power chain** (20 min):
   - Battery → TP4056 charger
   - TP4056 → AMS1117 regulator
   - AMS1117 → ESP32 3.3V

2. ☑️ **Toggle switch** (10 min):
   - COM terminal → ESP32 GPIO2
   - NO terminal → GND

3. ☑️ **LED strip** (20 min):
   - Cut to 8 LEDs
   - Solder wires: +5V, DIN, GND
   - Connect to ESP32

4. ☑️ **Test continuity** (10 min):
   - All grounds connected
   - No shorts
   - Voltage readings correct

**Detailed instructions**: [Soldering Guide](../assembly/soldering.md)

### Step 4: Flash Firmware (15 minutes)

**Connect ESP32** via USB-C to computer:

```bash
# Navigate to firmware directory
cd firmware/

# Build and flash (opens monitor automatically via espflash)
cargo run --release

# Only monitor serial output (if already flashed)
espflash monitor
```

**Expected output**:
```
Connecting to WiFi...
Connected! IP: 192.168.1.100
Starting main loop...
Device ready.
```

**Troubleshooting**: [Firmware Installation Guide](../firmware/installation.md)

### Step 5: Configure WiFi (5 minutes)

**Two methods**:

#### Method A: Configuration Portal (Easiest)

1. **Long press** toggle switch (3 seconds)
2. **Connect** to WiFi network: `WallClockIn_XXXXXX`
3. **Browser** opens automatically to http://192.168.4.1
4. **Enter** your WiFi credentials and API endpoint
5. **Save** - device restarts and connects

#### Method B: Hard-code in firmware

Edit `firmware/src/config.rs`:
```rust
pub const WIFI_SSID: &str = "YourNetworkName";
pub const WIFI_PASSWORD: &str = "YourPassword";
pub const API_ENDPOINT: &str = "https://your-api.com";
pub const API_TOKEN: &str = "your_bearer_token";
```

Re-upload firmware.

**Detailed instructions**: [Configuration Guide](../firmware/configuration.md)

### Step 6: Test & Verify (10 minutes)

**Test checklist**:

1. ☑️ **Power on** - Blue LED pulses (connecting)
2. ☑️ **WiFi connects** - LED turns red (idle)
3. ☑️ **Toggle down** - LED turns green, API called
4. ☑️ **Toggle up** - LED turns red, API called
5. ☑️ **Energy meter** - LEDs 2-8 show work duration
6. ☑️ **Battery** - Disconnect USB, still works

**If any step fails**: [Troubleshooting Guide](../troubleshooting/overview.md)

### Step 7: Enclosure (30-60 minutes)

**Option A: 3D Print** (if you have access to printer):
- Files in `/hardware/enclosure/`
- Print time: 5-6 hours
- Material: CHF 5 of PLA
- **FabLab EPFL** has 3D printers!

**Option B: Project Box**:
- Buy from Conrad or Brack (CHF 10)
- Drill holes for switch, USB, LEDs
- Time: 30 minutes

**Option C: Laser Cut Acrylic**:
- Files in `/hardware/enclosure/`
- **FabLab EPFL** has laser cutter!
- Material: CHF 8 of 3mm acrylic
- Cut time: 15 minutes

**Assembly**:
1. Mount ESP32 with standoffs
2. Mount switch in front panel
3. Position LED strip at top
4. Secure battery with double-sided tape
5. Close enclosure

**Detailed instructions**: [Enclosure Assembly](../assembly/enclosure.md)

### Step 8: Done! 🎉

**Your device is ready!**

Daily use:
- **Toggle DOWN** = Clock in (start work)
- **Toggle UP** = Clock out (stop work)
- **LEDs** = Energy meter shows hours worked
- **Battery** = Lasts 10-14 days per charge

**Next steps**:
- [Usage Guide](../usage/daily-operation.md) - Daily workflow
- [Customization](../firmware/customization.md) - Change colors, timings
- [Troubleshooting](../troubleshooting/overview.md) - Fix issues

## Estimated Costs

### Budget Build (CHF 40, 4 weeks)

| Item | Source | Price |
|------|--------|-------|
| ESP32-C3 kit | AliExpress | CHF 15 |
| LiPo + charger | AliExpress | CHF 10 |
| Components | AliExpress | CHF 8 |
| Enclosure | DIY/3D print | CHF 5 |
| **Total** | | **CHF 38** |
| **Time** | | **3-4 weeks** |

### Standard Build (CHF 90, 3 days)

| Item | Source | Price |
|------|--------|-------|
| ESP32-C3 | Digitec | CHF 15 |
| LEDs | Digitec | CHF 12 |
| Battery | Digitec | CHF 18 |
| Components | Conrad | CHF 30 |
| Enclosure | Conrad/Print | CHF 10 |
| USB cable | Digitec | CHF 5 |
| **Total** | | **CHF 90** |
| **Time** | | **2-3 days** |

### Premium Build (CHF 150, same day)

| Item | Source | Price |
|------|--------|-------|
| Quality components | Adafruit imports | CHF 100 |
| Professional tools | Conrad | CHF 30 |
| Custom enclosure | Laser cut acrylic | CHF 20 |
| **Total** | | **CHF 150** |
| **Time** | | **Same day at FabLab** |

**Note**: Tool costs are one-time investment, reusable for all future projects!

## Skill Requirements

### Minimum Requirements

**You can do this if you**:
- ✅ Can use a soldering iron (or willing to learn - 30 min)
- ✅ Can copy/paste commands in terminal
- ✅ Can edit text files
- ✅ Have patience for troubleshooting

**No experience needed**:
- ❌ Programming (firmware is ready)
- ❌ Electronics theory (guide explains everything)
- ❌ 3D modeling (files provided)

### Learning Curve

```
Hour 0-1:   Steep (first time soldering)
            └─ FabLab has instructors!

Hour 1-2:   Moderate (assembly)
            └─ Follow step-by-step guide

Hour 2-3:   Easy (programming)
            └─ Copy/paste commands

Hour 3+:    Using it! (daily operation)
            └─ Push button, done!
```

## Common Pitfalls

### ❌ Ordering Wrong Components

**Problem**: "I bought ESP8266, not ESP32-C3"

**Prevention**:
- Use exact model numbers from BOM
- Check pinout matches guide
- When in doubt, ask in Discussions

**Solution**:
- Return and reorder (Switzerland has good return policies!)
- Or adapt firmware (advanced)

### ❌ Soldering Shorts

**Problem**: "Device won't turn on, gets hot"

**Prevention**:
- Test with multimeter after each connection
- Use proper amount of solder
- Check for bridges with magnifying glass

**Solution**:
- Find short with multimeter continuity
- Desolder and redo joint
- Visit FabLab for help

### ❌ WiFi Won't Connect

**Problem**: "Blue LED keeps pulsing"

**Prevention**:
- Double-check SSID (case sensitive!)
- Ensure 2.4GHz network (not 5GHz)
- Check WiFi password carefully

**Solution**:
- Long press to enter config portal
- Reconfigure credentials
- See [WiFi Troubleshooting](../troubleshooting/connectivity.md)

### ❌ API Calls Fail

**Problem**: "Yellow LED flashing"

**Prevention**:
- Verify API endpoint URL (https://)
- Test API with curl first
- Check authentication token

**Solution**:
- Monitor serial output for errors
- Test API endpoint manually
- See [API Troubleshooting](../troubleshooting/api.md)

## Time Investment

### First Build

| Phase | Time | Can Skip? |
|-------|------|-----------|
| **Planning** | 30 min | No |
| **Ordering** | 30 min | No |
| **Waiting for parts** | 2-3 days | No |
| **Reading docs** | 1 hour | Partially |
| **Soldering** | 90 min | No |
| **Programming** | 30 min | No |
| **Testing** | 30 min | No |
| **Enclosure** | 60 min | Yes (temp) |
| **Troubleshooting** | 0-120 min | Hopefully! |
| **Total active** | **5-7 hours** | |
| **Total calendar** | **3-4 days** | |

### Second Build (Experience)

With experience, you can build in **2 hours**:

- Soldering: 45 min (know what you're doing)
- Programming: 10 min (reuse config)
- Testing: 15 min (know what to check)
- Enclosure: 30 min (have process down)

## Help & Resources

### 🇨🇭 Lausanne Local Resources

**FabLab EPFL**:
- Address: Bâtiment MX, EPFL Campus
- Tools: Free (EPFL) or small fee
- Help: Experienced makers available
- Website: [fablab.epfl.ch](https://fablab.epfl.ch/)

**Electrolab Renens**:
- Address: Near Lausanne
- Hackerspace with electronics
- Community: Friendly, helpful

**Conrad Electronics Geneva**:
- 40 min from Lausanne
- In-person component shopping
- Staff can help with questions

### Online Resources

**This Documentation**:
- [Hardware Guide](../hardware/overview.md)
- [Assembly Guide](../assembly/soldering.md)
- [Firmware Guide](../firmware/overview.md)
- [Troubleshooting](../troubleshooting/overview.md)

**Community**:
- [GitHub Discussions](https://github.com/yourusername/wallClockInMachine/discussions)
- [Issues](https://github.com/yourusername/wallClockInMachine/issues)

**General Learning**:
- [SparkFun Soldering Tutorial](https://learn.sparkfun.com/tutorials/how-to-solder-through-hole-soldering)
- [Adafruit NeoPixel Guide](https://learn.adafruit.com/adafruit-neopixel-uberguide)
 - [Rust on ESP-IDF (esp-idf)](https://esp-rs.github.io/book/)

## Next Steps

**Ready to start?**

1. **Read full documentation**:
   - [Hardware Overview](../hardware/overview.md)
   - [Bill of Materials](../hardware/bill-of-materials.md)
   - [Soldering Guide](../assembly/soldering.md)

2. **Order components**:
   - Use shopping list for Lausanne
   - 2-3 day delivery from Swiss suppliers

3. **Prepare tools**:
   - Visit FabLab EPFL
   - Or buy basic soldering kit

4. **Build!**:
   - Follow guides step-by-step
   - Ask for help if stuck
   - Share your success!

---

**Questions?** Ask in [GitHub Discussions](https://github.com/yourusername/wallClockInMachine/discussions)

**Stuck?** Visit [Troubleshooting Guide](../troubleshooting/overview.md)

**Want to contribute?** See [Development Guide](../development/contributing.md)

Let's build this! 🚀
