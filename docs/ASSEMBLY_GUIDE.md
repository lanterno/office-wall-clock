# Assembly Guide

**Time Required**: 2-3 hours  
**Skill Level**: Beginner to Intermediate  
**Tools Needed**: See [Bill of Materials](../hardware/BILL_OF_MATERIALS.md)

## Before You Begin

### Safety First! ⚠️

- Work in a well-ventilated area (solder fumes)
- Wear safety glasses
- Keep soldering iron away from flammable materials
- LiPo batteries can be dangerous - handle with care
- Have a fire extinguisher nearby (just in case!)

### Preparation Checklist

- [ ] All components received and verified
- [ ] Tools assembled and ready
- [ ] Enclosure printed or ready
- [ ] Work area clean and organized
- [ ] Read this guide completely once before starting

### Recommended Order

1. Test individual components first
2. Assemble electronics on breadboard (optional but recommended)
3. Test firmware before soldering
4. Solder permanent connections
5. Assemble into enclosure
6. Final testing

---

## Phase 1: Component Testing (30 minutes)

### Test 1: ESP32-C3 Board

**Purpose**: Verify the microcontroller works before soldering

```bash
# Connect ESP32-C3 to computer via USB-C cable
# Open Arduino IDE or PlatformIO
# Upload "Blink" example sketch
# LED should blink on the board
```

**Expected Result**: On-board LED blinks every second

✅ **Pass**: Continue to next test  
❌ **Fail**: Check USB cable, try different port, or replace board

### Test 2: LED Strip

**Wiring** (Temporary for testing):
```
LED Strip    →   ESP32-C3
─────────────────────────
VCC (Red)    →   3.3V
GND (White)  →   GND
DATA (Green) →   GPIO 8
```

**Test Code**: Upload FastLED "ColorPalette" example

**Expected Result**: LEDs cycle through colors

✅ **Pass**: LEDs work  
❌ **Fail**: Check wiring, verify it's 5V compatible, try different LED

### Test 3: Battery & Charger

**⚠️ IMPORTANT**: Only test battery with protection circuit!

**Steps**:
1. Connect battery to TP4056 charger module (BAT+ and BAT-)
2. Plug USB-C cable into TP4056
3. Red LED should light up (charging)
4. Measure voltage on OUT+ and OUT- (should be ~4.2V when full)

**Expected Result**: Battery charges, LEDs indicate status

✅ **Pass**: Charging system works  
❌ **Fail**: Check polarity, verify TP4056 module, test battery voltage

### Test 4: Toggle Switch

**Test**: Use multimeter in continuity mode
- Toggle to position 1: Common → Terminal 1 should beep
- Toggle to position 2: Common → Terminal 2 should beep

**Expected Result**: Clear continuity in each position

✅ **Pass**: Switch works  
❌ **Fail**: Clean contacts or replace switch

---

## Phase 2: Breadboard Prototype (1 hour)

**Why?** Test everything together before permanent soldering!

### Wiring Diagram

```
┌─────────────────────────────────────────────────────┐
│                                                     │
│  [ESP32-C3]                                        │
│   GPIO8 ──────────────► DATA (LED Strip)          │
│   GPIO9 ──────────┬───► Button (Common)           │
│                   │                                 │
│   3.3V ────┬──────┴───► LED Strip VCC             │
│            │                                        │
│   GND ─────┴──────────► All GND points            │
│                                                     │
│                                                     │
│  [TP4056 Charger]                                  │
│   OUT+ ────────────────► Voltage Regulator IN      │
│   OUT- ────────────────► GND                       │
│   BAT+ ───┐                                        │
│   BAT- ───┤ Battery (2000mAh LiPo)                │
│                                                     │
│  [Voltage Regulator (Optional)]                    │
│   OUT (3.3V) ──────────► ESP32 3.3V               │
│                                                     │
└─────────────────────────────────────────────────────┘
```

### Step-by-Step Breadboard Assembly

**Step 1**: Mount ESP32-C3 on breadboard center

**Step 2**: Connect power rails
- TP4056 OUT+ → Positive rail
- TP4056 OUT- / GND → Negative rail

**Step 3**: Connect toggle switch
- Common terminal → GPIO9
- One switch terminal → GND
- Other terminal → Open (not used)

**Step 4**: Connect LED strip (cut to 8 LEDs)
- VCC → Positive rail (3.3V or 5V via regulator)
- GND → Negative rail
- DATA → GPIO8

**Step 5**: Add bypass capacitor
- 100µF capacitor across power rails near ESP32

### Test Breadboard Circuit

1. Upload firmware (see [Firmware Installation](FIRMWARE_INSTALLATION.md))
2. Power on via USB
3. Device should boot and show blue LED (WiFi connecting)
4. Press button - should respond
5. LEDs should light up

**Troubleshooting**:
- No power: Check connections, battery charge
- LEDs don't work: Check DATA pin, verify 5V power if needed
- Button doesn't respond: Check pull-up resistor (internal should work)

---

## Phase 3: Permanent Soldering (1-1.5 hours)

### Preparation

**Organize Your Workspace**:
- Soldering iron on left (or right if left-handed)
- Solder spool nearby
- Components laid out in order
- Helping hands or PCB holder
- Damp sponge for cleaning iron tip

**Soldering Tips**:
- Tin the iron tip before each joint
- Heat the pad AND wire, then apply solder
- Use just enough solder (shiny joint, not a blob)
- Don't move joint for 2-3 seconds while cooling
- Check each joint before moving to next

### Soldering Order

**1. Power Distribution Board (Optional)**

Create a small power distribution board using prototype PCB:

```
Common Power Points:
  - Battery OUT+ → Multiple 3.3V outputs
  - GND → Multiple GND outputs
```

**2. Solder Wires to TP4056 Charger**

- BAT+ (red wire, 10cm) → Battery positive
- BAT- (black wire, 10cm) → Battery negative  
- OUT+ (red wire, 15cm) → Power distribution
- OUT- (black wire, 15cm) → Common ground

**Heat shrink** each connection!

**3. Solder Wires to ESP32-C3**

Option A: Solder directly to board pads (permanent)  
Option B: Use headers and female connectors (removable)

Recommended wires:
- GPIO8 (yellow, 15cm) → LED strip DATA
- GPIO9 (white, 15cm) → Toggle switch
- GPIO4 (green, 15cm) → Battery voltage sense (via divider)
- 3.3V (red, multiple)
- GND (black, multiple)

**4. Voltage Divider for Battery Sensing**

```
Battery+ ──┬── 10kΩ resistor ──┬── GPIO4 (ADC)
           │                    │
           │                    ├── 10kΩ resistor ── GND
```

This divides battery voltage (4.2V max) to safe level (2.1V) for ADC.

**5. Solder LED Strip**

- Cut strip after 8th LED (there are cut marks)
- Tin the copper pads on strip
- Solder wires to pads:
  - VCC (red, 10cm)
  - GND (black, 10cm)
  - DATA (yellow, 10cm)

**⚠️ Polarity matters!** Double-check before powering on.

**6. Solder Toggle Switch**

- Common terminal → GPIO9 wire
- One position terminal → GND
- Leave other terminal empty

Optionally add **10kΩ pull-up resistor** between GPIO9 and 3.3V (ESP32 has internal pull-up, so this is optional).

**7. USB-C Panel Connector**

- Solder wires from panel connector to TP4056 USB pads
- Or use TP4056 module with built-in USB-C

### Inspection Checklist

After soldering, inspect each joint:

- [ ] Shiny, not dull (good solder flow)
- [ ] No cold joints (gray, grainy appearance)
- [ ] No solder bridges between pins
- [ ] No loose wires
- [ ] All wires have heat shrink tubing
- [ ] Connections are mechanically strong

**Test with multimeter**:
- [ ] Continuity on all expected connections
- [ ] No shorts between power and ground
- [ ] Battery voltage present at regulator input

---

## Phase 4: Enclosure Assembly (30 minutes)

### Prepare Enclosure

**3D Printed Enclosure**:
1. Remove support material carefully
2. Sand any rough edges
3. Test-fit all components before gluing
4. Drill out toggle switch hole if needed (12mm)

**Purchased Project Box**:
1. Mark locations for toggle switch and USB port
2. Drill 12mm hole for switch (use step drill bit)
3. Cut rectangular slot for USB-C connector
4. Drill mounting holes for PCB standoffs

### Component Mounting

**Step 1: Install USB-C Panel Connector**
- Insert from outside
- Secure with mounting nut from inside
- Verify it sits flush

**Step 2: Install Toggle Switch**
- Insert switch through top hole
- Add lock washer and nut
- Tighten firmly (should not rotate)

**Step 3: Mount LED Light Pipe**
- Apply small amount of hot glue to edges
- Press frosted acrylic into front panel slot
- Wipe away excess glue

**Step 4: Position LED Strip**
- Stick LED strip behind light pipe (use adhesive backing)
- Position so LEDs align with diffuser
- Keep 2-3mm gap between LEDs and diffuser

**Step 5: Mount ESP32-C3**
- Use M3 standoffs (10mm height)
- Screw standoffs to bottom shell
- Place ESP32 on standoffs
- Secure with M3 screws

**Step 6: Mount TP4056 Charger**
- Use double-sided foam tape OR
- Hot glue to bottom shell
- Position near USB-C connector

**Step 7: Mount Battery**
- Place battery in remaining space
- Secure with double-sided foam tape
- **Do not glue directly!** (need to remove for replacement)
- Route wires neatly

### Cable Management

- Use small cable ties or twist ties
- Keep wires away from toggle switch mechanism
- Ensure no wires pinched when closing enclosure
- Leave some slack for serviceability

### Final Assembly

1. Double-check all connections one last time
2. Test device before closing (power on, verify LEDs work)
3. Align top cover with bottom shell
4. Insert M3 screws through bottom into top cover
5. Tighten screws evenly (don't overtighten!)
6. Apply rubber feet to bottom corners

---

## Phase 5: Final Testing (15 minutes)

### Power-On Test

1. **Charge battery fully** (USB-C, wait for blue LED on TP4056)
2. Press toggle switch to turn on
3. Device should boot:
   - Blue LED (WiFi connecting)
   - Should create hotspot "WallClockIn-Setup"

### LED Test

- Status LED should light up
- Try different states:
  - Red = Clocked out
  - Green = Clocked in
  - Blue = Connecting
  - Yellow = Error

### Button Test

- Press toggle switch
- Should transition between states
- Hold for 3 seconds → Config mode (white LED)

### WiFi Configuration Test

See [Configuration Guide](CONFIGURATION.md) for setup steps

### API Test

- Configure API endpoint
- Test clock in (button press)
- Verify API receives request
- Test clock out
- Check energy meter updates

### Battery Test

- Unplug USB-C
- Device should run on battery
- Check battery indicator in logs
- Should last multiple days

---

## Troubleshooting

### Problem: Device doesn't power on

**Possible Causes**:
- Battery not charged
- Loose battery connection
- Dead battery
- Switch not connected properly

**Solutions**:
1. Plug in USB-C to charge
2. Check battery voltage with multimeter (should be 3.0V+)
3. Verify connections to TP4056
4. Check toggle switch wiring

### Problem: LEDs don't light up

**Possible Causes**:
- Wrong DATA pin
- Power issue (LEDs need 5V ideally)
- Damaged LED strip
- Incorrect wiring

**Solutions**:
1. Verify DATA connected to GPIO8
2. Check LED power supply voltage
3. Test LED strip separately
4. Look for solder bridges

### Problem: Button doesn't respond

**Possible Causes**:
- GPIO9 not connected
- Switch faulty
- Debounce issue

**Solutions**:
1. Test switch with multimeter
2. Check wiring to GPIO9
3. Try external pull-up resistor (10kΩ)

### Problem: Won't connect to WiFi

**Possible Causes**:
- Incorrect credentials
- 5GHz network (ESP32 only supports 2.4GHz)
- Network security issues

**Solutions**:
1. Reset config (hold button during boot)
2. Enter setup mode manually
3. Check router settings (WPA2 personal supported)

### Problem: Battery drains quickly

**Possible Causes**:
- LEDs too bright
- Deep sleep not working
- High power consumption

**Solutions**:
1. Reduce LED brightness in config
2. Enable deep sleep mode
3. Check for short circuits
4. Replace battery if old

---

## Maintenance

### Regular Maintenance (Monthly)

- Clean LED light pipe with microfiber cloth
- Check toggle switch tightness
- Verify USB-C port is clean
- Check battery runtime

### Annual Maintenance

- Check all solder joints for cracks
- Tighten screws if loose
- Test battery capacity (may need replacement after 3-5 years)
- Update firmware to latest version

---

## Modifications & Upgrades

### Add External Antenna

For better WiFi range, add external antenna to ESP32-C3

### Upgrade Battery

Replace 2000mAh with 3000mAh for longer runtime

### Add OLED Display

Mount small OLED to show time remaining (requires firmware mod)

### Wireless Charging

Add Qi wireless charging module for cable-free charging

---

## Congratulations! 🎉

You've successfully built your Wall Clock In Machine!

**Next Steps**:
1. Read [Configuration Guide](CONFIGURATION.md) to set up WiFi and API
2. Read [Usage Guide](USAGE_GUIDE.md) for daily operation
3. Check [Troubleshooting Guide](TROUBLESHOOTING.md) if issues arise

**Share Your Build**:
- Take photos of your finished device
- Post on social media with #WallClockInMachine
- Submit improvements via GitHub PR

---

**Need Help?** Open an issue on GitHub or check the FAQ!
