# Soldering Guide

Learn how to solder all components for the Wall Clock In Machine. This guide is beginner-friendly with detailed photos and tips.

!!! warning "Safety First"
    - Work in a well-ventilated area (solder fumes)
    - Use safety glasses
    - Don't touch the iron tip (350°C!)
    - Wash hands after soldering
    - Keep iron stand stable

## Before You Start

### Tools You'll Need

| Tool | Purpose | Price (CHF) | Where to Get |
|------|---------|-------------|--------------|
| **Soldering Iron** | Join connections | 20-80 | Digitec, Conrad |
| **Solder** | 60/40 tin/lead, 0.8mm | 5-10 | Conrad, Brack |
| **Wire Strippers** | Strip insulation | 10-15 | Jumbo, Brico+Loisirs |
| **Flush Cutters** | Cut wires/leads | 8-12 | Conrad |
| **Multimeter** | Test connections | 15-30 | Digitec |
| **Helping Hands** | Hold components | 10-15 | Digitec |
| **Solder Wick** | Remove mistakes | 3-5 | Conrad |
| **Flux Pen** | Improve flow | 5-8 | Conrad |

**Budget**: CHF 80-100 (reusable for all future projects!)

**Lausanne Tip**: Visit **FabLab EPFL** - they have all tools available for free (with EPFL access) or small membership fee.

### Materials Needed

From your [Bill of Materials](../hardware/bill-of-materials.md):

- [ ] ESP32-C3 DevKit
- [ ] WS2812B LED Strip (8 LEDs)
- [ ] SPDT Toggle Switch
- [ ] 2000mAh LiPo Battery
- [ ] TP4056 Charger Module
- [ ] AMS1117 Regulator Module
- [ ] 330Ω Resistor (optional)
- [ ] 1000µF Capacitor (optional)
- [ ] Hookup wire (22-26 AWG)
- [ ] JST connectors (optional)
- [ ] Heat shrink tubing

### Soldering Iron Setup

**Temperature Settings**:

| Material | Temperature | Notes |
|----------|-------------|-------|
| **60/40 Solder** | 350°C (662°F) | Standard |
| **Lead-free Solder** | 380°C (716°F) | EU compliant |
| **Heat Shrink** | 100°C (212°F) | Use heat gun |

**Recommended**: Start at 350°C and adjust if needed.

**Tip Selection**:
- **Chisel tip** (recommended) - Versatile, good heat transfer
- **Conical tip** - Precise, small joints
- **Bevel tip** - Large pads

## Soldering Basics

### The Perfect Solder Joint

A good solder joint looks like this:

```
Side View:
        Shiny, smooth cone
             ╱╲
Component ──●  ●── PCB pad
           ╱    ╲
```

**Good Joint**:
- ✅ Shiny, smooth surface
- ✅ Cone/volcano shape
- ✅ Flows onto both pad and lead
- ✅ Concave fillet around lead

**Bad Joints**:
- ❌ **Cold joint**: Dull, grainy (reheat)
- ❌ **Too much solder**: Blob, bridges
- ❌ **Too little solder**: Doesn't fill joint
- ❌ **Burnt flux**: Black, overheated

### The 5-Second Technique

Perfect solder joints in 5 steps:

```
1. CLEAN (1 sec)
   Wipe tip on damp sponge
   
2. HEAT (2 sec)
   Touch iron to pad AND lead
   
3. FEED (1 sec)
   Touch solder to joint (not iron!)
   Solder flows into joint
   
4. REMOVE (1 sec)
   Remove solder, then iron
   
5. COOL (3 sec)
   Don't move! Let solidify
```

**Total time**: 5 seconds of heat

**Why this works**:
- Short heat time prevents damage
- Solder flows to hot surfaces
- Clean tip improves heat transfer
- Proper order creates strong joint

### Common Mistakes

| Problem | Cause | Solution |
|---------|-------|----------|
| **Solder won't stick** | Dirty/oxidized | Clean with flux |
| **Solder balls up** | Too hot or dirty | Lower temp, clean tip |
| **Components move** | Moved while cooling | Use helping hands |
| **Burnt smell** | Too hot | Lower temperature |
| **Solder bridges** | Too much solder | Use solder wick |

## Step-by-Step Assembly

### Step 1: Prepare Components

**Cut wires to length**:

| Connection | Length | Color |
|------------|--------|-------|
| Battery → TP4056 | 5cm | Red/Black |
| TP4056 → AMS1117 | 8cm | Red/Black |
| AMS1117 → ESP32 | 10cm | Red/Black |
| ESP32 → LEDs | 15cm | Red/Black/White |
| ESP32 → Switch | 12cm | Black/White |

**Strip wires**:
- Strip 3-5mm from each end
- Twist strands together
- Tin with small amount of solder

**Organize workspace**:
```
Layout (looking down at desk):

[Helping Hands]  [Component Box]
                 
[Soldering Iron] [Work Area]     [Multimeter]
     ↓
  [Stand]        [Sponge]        [Solder/Flux]
```

### Step 2: Solder Power System

**Objective**: Connect Battery → Charger → Regulator → ESP32

#### 2.1 Battery to TP4056 Charger

!!! danger "Battery Safety"
    - **Never short battery wires!**
    - Work with one wire at a time
    - Cover exposed wire with heat shrink immediately
    - If using battery with connector, DON'T solder - use connector!

**If battery has JST connector** (recommended):
- ✅ Skip soldering, plug directly into TP4056
- TP4056 modules usually have JST socket

**If battery has bare wires**:

1. **Red wire (Battery +)**:
   ```
   a. Slide heat shrink onto wire
   b. Tin wire end (small amount of solder)
   c. Tin TP4056 BAT+ pad
   d. Heat both, solder flows together
   e. Remove heat, let cool 5 seconds
   f. Slide heat shrink over joint, apply heat gun
   ```

2. **Black wire (Battery -)**:
   ```
   Same process for BAT- pad
   ⚠️ Don't let red and black wires touch!
   ```

3. **Test**:
   ```
   Multimeter → DC Voltage mode
   Red probe → BAT+ pad
   Black probe → BAT- pad
   Reading: 3.7-4.2V ✓
   ```

**Diagram**:
```
Battery (JST connector)
  ↓
  Red (+) ──→ TP4056 [BAT+]
  Black (-) ──→ TP4056 [BAT-]
```

#### 2.2 TP4056 to AMS1117 Regulator

**Connection**:
- TP4056 OUT+ → AMS1117 VIN
- TP4056 OUT- → AMS1117 GND

**Steps**:

1. Cut two 8cm wires (red, black)
2. Strip and tin all ends
3. Solder red to TP4056 OUT+ pad
4. Solder red to AMS1117 VIN pad
5. Solder black to TP4056 OUT-/GND
6. Solder black to AMS1117 GND
7. Add heat shrink to all joints

**Diagram**:
```
TP4056         AMS1117
[OUT+] ──Red──→ [VIN]
[OUT-] ──Blk──→ [GND]
```

#### 2.3 AMS1117 to ESP32-C3

**Connection**:
- AMS1117 VOUT → ESP32 3V3 pin
- AMS1117 GND → ESP32 GND pin

**Steps**:

1. Cut two 10cm wires (red, black)
2. Strip and tin
3. Solder to AMS1117 VOUT and GND
4. **Don't solder to ESP32 yet** - we'll do this later

**Diagram**:
```
AMS1117        ESP32-C3
[VOUT] ──Red──→ [3V3]  ← Later
[GND]  ──Blk──→ [GND]  ← Later
```

**Test Power Chain**:
```
1. Plug USB-C into TP4056
2. Multimeter: Check AMS1117 VOUT
   Should read: 3.3V ± 0.1V
3. If correct: ✓ Power system works!
4. If not: Check all connections with multimeter continuity
```

### Step 3: Solder Toggle Switch

**Objective**: Connect switch to ESP32 GPIO2

#### 3.1 Identify Switch Terminals

SPDT switch has 3 terminals:

```
     [COM] ← Common (middle terminal)
       ↓
   ────┴────
  │    ●    │
  │  ╱   ╲  │
  │ ●     ● │
   ─────────
    ↑     ↑
   [NC]  [NO]
    ↑     ↑
  Not   Normally
  Used   Open
```

**Our wiring**:
- COM → ESP32 GPIO2
- NO → GND
- NC → Not connected

#### 3.2 Solder Wires

1. **COM terminal**:
   ```
   - Cut 12cm white/yellow wire
   - Strip and tin
   - Solder to COM terminal
   - Add heat shrink
   ```

2. **NO terminal**:
   ```
   - Cut 12cm black wire  
   - Strip and tin
   - Solder to NO terminal
   - Add heat shrink
   ```

3. **Test**:
   ```
   Multimeter → Continuity mode
   - Switch UP: COM-NO should beep ✓
   - Switch DOWN: COM-NO no beep ✓
   ```

**Diagram**:
```
Switch         ESP32-C3
[COM] ──Wht──→ [GPIO2]  ← Later
[NO]  ──Blk──→ [GND]    ← Later
[NC]  (empty)
```

### Step 4: Prepare LED Strip

**Objective**: Prepare 8 LEDs for connection

#### 4.1 Cut LED Strip

If you bought a 1-meter strip (60 LEDs):

1. **Locate cut marks**:
   ```
   LED strip has copper pads every 3 LEDs:
   
   [LED][LED][LED] ✂️ [LED][LED][LED] ✂️
        ↑
     Cut here (copper pad)
   ```

2. **Cut after 8th LED**:
   - Use flush cutters
   - Cut through middle of copper pad
   - Leave copper on both sides

3. **Identify connections**:
   ```
   First LED (input end):
   [+5V] [DIN] [GND]
     ↑     ↑     ↑
    Red  White  Black
    
   Last LED (output end):
   [+5V] [DOUT] [GND]  ← Not used
   ```

#### 4.2 Solder LED Wires

**Input end** (where data enters):

1. **Power wire (+5V)**:
   ```
   - Cut 15cm RED wire
   - Strip 3mm, tin
   - Solder to +5V pad
   - Add heat shrink
   ```

2. **Data wire (DIN)**:
   ```
   - Cut 15cm WHITE/YELLOW wire
   - Strip 3mm, tin
   - Solder to DIN pad
   - Add heat shrink
   ```

3. **Ground wire (GND)**:
   ```
   - Cut 15cm BLACK wire
   - Strip 3mm, tin
   - Solder to GND pad
   - Add heat shrink
   ```

**Optional: Add capacitor** (smooths power):

If you have a 1000µF capacitor:
```
- Solder capacitor between LED +5V and GND
- Orientation matters! Negative stripe → GND
- Helps prevent LED flickering
```

**Optional: Add resistor** (protects data line):

If you have a 330Ω resistor:
```
- Solder resistor in series with DIN wire
- Prevents data line damage
- Not critical for 8 LEDs
```

**Diagram**:
```
LED Strip (input)    ESP32-C3
[+5V] ──Red─────────→ [5V or 3.3V]  ← Later
[DIN] ──Wht─[330Ω]──→ [GPIO3]       ← Later
[GND] ──Blk─────────→ [GND]         ← Later
              ↑
         Optional resistor
         
     [1000µF]  ← Optional capacitor
        ↓
      [GND]
```

### Step 5: Assemble on ESP32-C3

**Objective**: Connect everything to ESP32

#### 5.1 ESP32-C3 Pinout Reference

```
ESP32-C3-DevKitM-1 (Top View)
┌────────────────────────┐
│  ○ USB-C Port          │
├────────────────────────┤
│ 3V3  ●─────────● GND   │ ← Power
│ EN   ●         ● GPIO18│
│ G04  ●         ● GPIO19│
│ G05  ●         ● GPIO10│
│ G06  ●         ● GPIO09│ ← USB D-
│ G07  ●         ● GPIO08│ ← USB D+
│ G21  ●         ● GPIO07│
│ G20  ●         ● GPIO06│
│ G10  ●         ● GPIO05│
│ G03  ●         ● GPIO04│ ← LED Data
│ G02  ●         ● GPIO03│ ← Button
│ G01  ●         ● GPIO02│
│ G00  ●         ● GPIO01│
│ GND  ●─────────● 5V    │ ← Power (USB only)
└────────────────────────┘
```

#### 5.2 Solder Power Wires

1. **3.3V Power** (from AMS1117):
   ```
   - Take red wire from AMS1117
   - Solder to ESP32 3V3 pin
   - This powers the ESP32
   ```

2. **Ground** (from AMS1117):
   ```
   - Take black wire from AMS1117
   - Solder to ESP32 GND pin (left side)
   - Common ground for everything
   ```

!!! tip "Alternative: USB Power"
    If testing without battery:
    - Power ESP32 via USB-C port
    - No need to connect 3V3 from regulator yet

#### 5.3 Solder Switch Wires

1. **Switch COM → GPIO2**:
   ```
   - Take white wire from switch COM
   - Solder to ESP32 GPIO2 pin
   - This is the input pin
   ```

2. **Switch NO → GND**:
   ```
   - Take black wire from switch NO
   - Solder to ESP32 GND pin (right side)
   - Can share GND with power GND
   ```

**Enable internal pull-up** (in firmware):
```cpp
pinMode(GPIO_NUM_2, INPUT_PULLUP);
// Now GPIO2 reads HIGH when switch open
//           reads LOW when switch closed
```

#### 5.4 Solder LED Wires

1. **LED Data → GPIO3**:
   ```
   - Take white wire from LED DIN
   - Solder to ESP32 GPIO3 pin
   - Critical: Data signal must be clean
   ```

2. **LED Power → 5V**:
   ```
   - Take red wire from LED +5V
   - Option A: Solder to ESP32 5V pin (only works when USB connected!)
   - Option B: Connect to battery voltage (3.7V, LEDs dimmer)
   - Recommended: Use 5V pin, ensure USB connected
   ```

3. **LED Ground → GND**:
   ```
   - Take black wire from LED GND
   - Solder to ESP32 GND pin
   - Share with other grounds
   ```

!!! warning "LED Power Consideration"
    - **5V option**: LEDs full brightness, but only works with USB
    - **3.7V option**: LEDs dimmer, works on battery
    - **Best**: Use 5V and keep device plugged in, or use boost converter for 5V from battery

### Step 6: Final Assembly

#### 6.1 Check All Connections

Use multimeter continuity mode:

| Test | Expected Result |
|------|-----------------|
| Battery + to AMS1117 VIN | Beep ✓ |
| AMS1117 VOUT to ESP32 3V3 | Beep ✓ |
| All GNDs together | Beep ✓ |
| Switch COM to GPIO2 | Beep ✓ |
| LED DIN to GPIO3 | Beep ✓ |
| **Battery + to GND** | **NO beep** ✓ (no short!) |

#### 6.2 Visual Inspection

Check each solder joint:

- [ ] Shiny, smooth surface
- [ ] No solder bridges between adjacent pins
- [ ] Wires secure (gentle tug test)
- [ ] Heat shrink covering all exposed metal
- [ ] No loose strands of wire

#### 6.3 First Power-On Test

**Before uploading firmware**:

1. **Connect USB-C to TP4056**:
   - Charger red LED should light (charging)
   - After 2-3 hours, blue/green LED (charged)

2. **Disconnect USB, wait 10 seconds**

3. **Check voltages**:
   ```
   Multimeter DC voltage mode:
   
   Battery:  3.7-4.2V ✓
   AMS1117:  3.3V ±0.1V ✓
   ESP32:    Should not be powered yet (no firmware)
   ```

**If voltages wrong**:
- Check connections with continuity mode
- Look for cold solder joints (dull appearance)
- Reflow suspicious joints

## Desoldering (Fixing Mistakes)

### Method 1: Solder Wick

1. Place copper braid over joint
2. Press hot iron on top
3. Solder wicks into braid
4. Remove braid and iron together

### Method 2: Solder Sucker

1. Melt solder joint
2. Place sucker nozzle next to joint
3. Press button - vacuum sucks solder
4. Repeat if needed

### Method 3: Add More Solder

Counterintuitive but works:

1. Add fresh solder to joint
2. Helps heat flow
3. Remove with wick/sucker
4. Cleaner than trying to desolder dry joint

## Soldering Tips & Tricks

### For Beginners

**Practice first**:
- Buy practice PCB kit (CHF 5)
- Or practice on old electronics
- Master technique before your project

**Go slow**:
- Rush = mistakes
- Each joint takes 5 seconds
- Take breaks every 15 minutes

**Good lighting**:
- Use desk lamp
- Magnifying glass helps
- See what you're doing!

### Temperature Troubleshooting

| Problem | Too Cold | Just Right | Too Hot |
|---------|----------|------------|---------|
| **Solder flow** | Slow, lumpy | Smooth, fast | Too fast |
| **Joint appearance** | Dull, grainy | Shiny, smooth | Burnt, black |
| **Flux** | Doesn't activate | Active, clean | Burnt, smoking |
| **Components** | Lifted pads | No damage | Burnt, delaminated |

**Solution**:
- Too cold: Increase 10°C
- Too hot: Decrease 20°C
- Find sweet spot: Smooth flow, no burning

### Wire Management

**Color coding**:
- 🔴 Red: Positive voltage
- ⚫ Black: Ground
- 🟡 Yellow/White: Signals
- 🔵 Blue: Optional/special

**Cable ties**:
- Group related wires
- Prevents tangles
- Looks professional

**Strain relief**:
- Add hot glue at solder joints
- Prevents wire breakage
- Especially for moving parts

## Testing & Validation

### Continuity Tests

**What to test**:
```
✓ Power path: Battery → Regulator → ESP32
✓ Ground continuity: All GND pins connected
✓ Button circuit: Switch COM → GPIO2
✓ LED circuit: ESP32 GPIO3 → LED DIN
✗ NO shorts: Power to GND should NOT beep
```

### Voltage Tests

**Expected readings**:
```
Battery:        3.7-4.2V
Regulator IN:   3.7-4.2V (same as battery)
Regulator OUT:  3.3V ±0.1V
ESP32 3V3 pin:  3.3V ±0.1V
LED +5V:        5.0V (USB) or 3.7V (battery)
```

### Resistance Tests

**Power off, check**:
```
Battery + to GND:    >1MΩ (no short)
ESP32 3V3 to GND:    >10kΩ (normal)
GPIO2 to GND:        >10kΩ (pull-up enabled in firmware)
```

## Common Issues

### Solder Won't Stick

**Causes**:
- Oxidized components
- Dirty soldering iron tip
- Temperature too low
- No flux

**Solutions**:
1. Clean tip on damp sponge
2. Apply flux pen to joint
3. Increase temperature 10°C
4. Use fresh solder (has flux core)

### Cold Solder Joint

**Appearance**:
- Dull, grainy surface
- Lumpy, irregular shape
- Doesn't flow smoothly

**Fix**:
1. Reheat joint with clean tip
2. Add tiny bit fresh solder
3. Let flow completely
4. Remove heat, don't move

### Solder Bridge

**Problem**: Solder connects adjacent pins

**Fix**:
1. Add flux to bridge
2. Heat with clean tip
3. Drag tip along pins
4. Surface tension separates solder
5. Or use solder wick

### Burnt Component

**Signs**:
- Discoloration
- Smoke during soldering
- Component doesn't work

**Prevention**:
- Solder quickly (<5 sec)
- Lower temperature if smoking
- Use heat sink (alligator clip on wire)

**If burnt**:
- Desolder and replace
- Most modules are cheap (<CHF 5)

## Next Steps

Soldering complete! ✓

**Continue to**:

- [**Wiring Diagram**](wiring.md) - Visual reference
- [**Enclosure Assembly**](enclosure.md) - Build the box
- [**Firmware Installation**](../firmware/installation.md) - Upload code

**Or if issues**:

- [**Troubleshooting - Hardware**](../troubleshooting/hardware.md) - Fix problems
- [**Rework Guide**](rework.md) - Fix mistakes

---

**Questions?** Ask in [GitHub Discussions](https://github.com/yourusername/wallClockInMachine/discussions) or visit **FabLab EPFL** for in-person help!
