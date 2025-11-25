# Enclosure Design

**Professional, Minimal, Desk-Friendly Design**

## Design Philosophy

The Wall Clock In Machine should:
- Look **professional** on your desk (not like a DIY hack)
- Be **intuitive** to use (obvious what the button does)
- Have **personality** (fun but not childish)
- Be **durable** (survives daily button presses)
- Be **compact** (doesn't dominate desk space)

## Dimensions

### External Dimensions
```
Width:  100 mm (3.94 inches)
Depth:   60 mm (2.36 inches)
Height:  35 mm (1.38 inches)
Weight: ~120 grams (4.2 oz)
```

**Size Comparison**: About the size of a deck of cards (but wider and flatter)

### Internal Dimensions
```
Usable Space: 90 × 50 × 28 mm
Wall Thickness: 2.5 mm (3D print) or 2.0 mm (injection mold)
Corner Radius: 3 mm (soft edges)
```

## Overall Design Concept

The enclosure consists of:
- **Top**: Toggle switch centered near front edge
- **Front**: LED light bar (8 LEDs) across full width
- **Right Side**: USB-C charging port
- **Bottom**: Four rubber feet at corners
- **Internal**: Bottom shell houses all electronics (ESP32-C6 DevKitC-1, battery, TP4056 charger, regulator)

## Detailed Component Layout

### Top Surface

**Toggle Switch Position**:
- Center: 50mm from left/right edges
- Position: 20mm from front edge
- Mounting: 12mm diameter hole
- Access: Finger clearance above and to sides

**Surface Finish**:
- Matte or light texture (hides fingerprints)
- Optional: Laser engraved "IN" / "OUT" near switch
- Optional: Company logo or personal design

### Front Panel

**LED Light Bar**:
- Position: Full width, 10mm from top edge
- Window: 90mm × 8mm transparent slot
- Implementation: Clear acrylic insert or translucent 3D print
- Diffuser: Frosted finish for even light distribution

**Aesthetic**: LEDs should glow softly, not blast your eyes 🔦→💡

### Side Panel (Right Side)

**USB-C Port**:
- Position: Center of right panel, 15mm from bottom
- Hole: 9mm × 3.5mm slot
- Mounting: Panel-mount connector with nut
- Cable Management: Recessed area inside for connector body

**Label**: Optional "⚡ CHARGE" text engraved next to port

### Bottom Panel

**Rubber Feet**:
- 4 feet at corners
- Position: 8mm from edges
- Size: 10mm diameter × 3mm height
- Material: Self-adhesive rubber/silicone
- Purpose: Prevent sliding, protect desk surface

**Optional Features**:
- Screw holes for wall mounting (4 × M4 holes)
- Battery access door (if you want easy replacement)
- Ventilation slots (not necessary but looks cool)

### Internal Structure

**Component Mounting**:
- ESP32-C3 PCB: M3 standoffs (4 corners)
- Battery (2000mAh): Hot glue or double-sided tape
- TP4056 Charger: Hot glue
- AMS1117-3.3V Regulator: Hot glue or tape
- LED Strips: Double-sided tape to front panel
- Toggle Switch: 12mm hole, mounted with lock nut

**Wire Management**:
- Keep wires short (< 10cm each)
- Use cable ties or clips for organization
- Color code: Red = power, Black = ground, Others = data
- Label wires with tape if needed during assembly

## Material Selection

### 3D Printing (Recommended for DIY)

**Material: PLA or PETG**

| Property | PLA | PETG | Winner |
|----------|-----|------|--------|
| **Ease of Print** | Very Easy | Medium | PLA ✅ |
| **Durability** | Good | Better | PETG ✅ |
| **Temperature Resistance** | 50°C | 70°C | PETG ✅ |
| **Surface Finish** | Excellent | Good | PLA ✅ |
| **Cost** | $20/kg | $25/kg | PLA ✅ |

**Verdict**: Use **PLA** for desk use (indoor, controlled temp). Use **PETG** if in hot environments.

**Print Settings**:
```yaml
Layer Height: 0.2mm (balance quality/speed)
Infill: 20% (strong enough, saves material)
Perimeters: 3 (strong walls)
Top/Bottom Layers: 4
Supports: Yes (for overhangs > 45°)
Brim/Raft: Brim (helps adhesion)
Print Speed: 50mm/s
Nozzle Temp: 215°C (PLA) / 240°C (PETG)
Bed Temp: 60°C (PLA) / 80°C (PETG)
```

**Color Options**:
- 🖤 **Black**: Professional, sleek, hides imperfections
- ⚪ **White**: Clean, modern, Apple-esque
- 🌫️ **Gray**: Neutral, industrial
- 🟦 **Blue**: Playful, tech-y
- 🌈 **Gradient**: Mix colors for unique look!

### Alternative Materials

**Laser-Cut Acrylic**:
- Pros: Crystal clear panels, precise cuts, modern aesthetic
- Cons: Fragile, harder to assemble, more expensive
- Cost: ~$15 for sheets + cutting service

**Injection-Molded ABS** (for production):
- Pros: Mass production, very durable, professional finish
- Cons: Requires mold ($500-5000), minimum order quantity
- Use: If making 100+ units

**Wood** (for artisanal look):
- Pros: Unique, warm aesthetic, easy to work with
- Cons: Harder to fit electronics precisely, humidity issues
- Best: Walnut, maple, or bamboo

## Assembly Method

### Snap-Fit Design (Recommended)

The enclosure consists of 3 parts:
1. **Bottom Shell**: Contains all electronics
2. **Top Cover**: Has toggle switch hole
3. **Front Light Panel**: Transparent LED window

**Assembly Steps**:
1. Mount all electronics in bottom shell
2. Connect wires and test
3. Snap front light panel into bottom shell
4. Screw top cover on (4 × M3 screws from bottom)

**Advantages**:
- ✅ Easy to open for maintenance
- ✅ No glue needed
- ✅ Modular design
- ✅ Can replace parts

### Alternative: Friction Fit

Top and bottom press together tightly, no screws.

**Pros**: Cleaner look, no visible fasteners
**Cons**: Harder to open, may loosen over time

## LED Light Pipe Design

The front panel needs to diffuse LED light evenly.

### Option 1: Frosted Acrylic Insert

**Method**:
1. Cut clear acrylic to 90mm × 8mm × 2mm
2. Sand with 220-grit sandpaper (both sides) for frosted effect
3. Press-fit into front panel slot
4. LED strip mounted 3mm behind acrylic

**Effect**: Smooth, even glow. Professional look. 🌟

### Option 2: Translucent 3D Print

**Method**:
1. Print front panel with white or clear filament
2. Use 100% infill for LED window area
3. Sand smooth and polish with heat gun briefly

**Effect**: Decent diffusion, one-piece design, easier. ✨

### Option 3: Diffusion Film

**Method**:
1. Cut window in front panel
2. Apply frosted vinyl film or diffusion paper
3. LED strip behind film

**Effect**: Quick, cheap, replaceable. Good enough! ✅

## Aesthetic Touches

### Engravings / Labels

**Top Surface Options**:
- Minimalist: "IN" / "OUT" near switch
- Symbols: Up/down arrows (▲ ▼)
- Custom: Company logo or personal design

### Color Accents

- Toggle switch cap: Contrasting color (e.g., red)
- LED window: Smoked acrylic (looks off when LEDs are off)
- USB port: Color-matched grommet

### Brand Identity

Add your personal touch:
- Laser engrave your initials on bottom
- 3D print your company logo on top
- Custom color scheme matching your desk setup

## Ergonomics

### Button Feel

**Toggle Switch Specifications**:
- Actuation Force: ~200-300g (satisfying click)
- Travel Distance: ~5mm
- Sound: Audible "click" for feedback
- Feel: Should be firm but not stiff

**Placement Rationale**:
- Top center = easy to reach without looking
- Elevated position = can press while holding device
- Space around = won't accidentally hit

### Visual Feedback

**LED Brightness**:
- Status LED: Medium bright (always visible but not distracting)
- Energy Meter: Dimmer (ambient lighting)
- Night Mode: Auto-dim after 6 PM (optional firmware feature)

### Desk Placement

**Optimal Position**:
- Within arm's reach from keyboard
- Not blocking monitor
- Near edge of desk (easy access when arriving/leaving)
- Cable management: USB cable can reach outlet/laptop

**Rubber Feet Design**:
- Should grip desk without leaving marks
- Allow device to be picked up with one hand
- Prevent sliding when button is pressed hard

## Ventilation & Heat Management

**Heat Generation**:
- ESP32-C3: Minimal heat (~0.3W typical)
- LEDs: ~0.5W (not much when only few lit)
- Charging: TP4056 gets warm (~1W during charge)

**Cooling Strategy**:
- Passive cooling (no fan needed)
- Optional: Small vent slots on bottom (hidden by rubber feet)
- Material: PLA conducts heat poorly but fine for this application
- Spacing: Keep 2mm clearance around hot components

**No ventilation needed for normal use!** Only gets warm during charging.

## Durability & Wear

### Expected Lifespan

**Components**:
- Toggle Switch: 50,000 cycles = 137 years of daily use ✅
- LEDs: 50,000 hours = 17 years of 8hr/day use ✅
- Battery: 300-500 cycles = 4-7 years ⚠️ (replaceable!)
- 3D Print: Indefinite if handled gently ✅

**Weak Points**:
- USB port: Can wear out, use magnetic cable adapter
- Toggle switch: Mounting nut may loosen, check yearly
- Battery: Will degrade, design for easy replacement

### Maintenance

**Annual Checkup**:
- Tighten toggle switch nut if loose
- Clean dust from LED window with microfiber cloth
- Check USB port for debris
- Verify battery health (check runtime)

**Every 5 Years**:
- Replace battery (capacity degrades)
- Re-tighten all internal screws
- Update firmware (new features!)

## Design Variations

### Compact Version (Mini)

- Dimensions: 70 × 50 × 25 mm
- Battery: 1000mAh
- LEDs: 4 LEDs (minimal energy meter)
- Use Case: Travel, minimal desk space

### Deluxe Version (Pro)

- Dimensions: 120 × 70 × 40 mm
- Battery: 3000mAh
- LEDs: 16 LEDs (detailed energy meter)
- Extra: OLED display showing time remaining
- Use Case: Power users, detailed tracking

### Wall-Mounted Version

- Mounting: 2 × keyhole slots on back
- Battery: Optional (can be USB-powered)
- Orientation: Vertical (LEDs in column)
- Use Case: Fixed desk setup, always plugged in

## CAD Files & Templates

### Provided Files

**Location**: `hardware/enclosure/`

- `wall_clock_v1.step` - CAD source (Fusion 360)
- `bottom_shell.stl` - 3D print ready
- `top_cover.stl` - 3D print ready
- `front_panel.stl` - 3D print ready
- `light_pipe_template.dxf` - Laser cutting (acrylic)
- `assembly_drawing.pdf` - Exploded view
- `drilling_template.pdf` - For project box alternative

### Customization Tips

**To Modify Design**:
1. Open `wall_clock_v1.step` in Fusion 360 (free for personal use)
2. Edit dimensions, add features
3. Export as STL for 3D printing
4. Slice with Cura or PrusaSlicer

**Common Modifications**:
- Resize to fit larger battery
- Add mounting bosses for extra PCBs
- Change button to push-button instead of toggle
- Add speaker hole for audio feedback
- Emboss your name/logo

## Manufacturing Options

### DIY 3D Print at Home

- Cost: roughly $2 of filament
- Time: 6-8 hours print time

### Online 3D Print Service

- Examples: Shapeways, Craftcloud, i.materialise, Xometry
- Cost: roughly $10-20 per enclosure
-,Time: 5-10 days including shipping

### Local Makerspace

- Cost: typical material + membership fees
- Time: print in one session

### CNC / Laser Cutting Service

- Materials: wood, acrylic, aluminum
- Cost: higher, suitable for more robust enclosures

## Next Steps

1. Review CAD files in `hardware/enclosure/`
2. Choose material and color
3. 3D print or order the enclosure
4. While waiting, prep the electronics (see [Assembly Guide](../assembly/soldering.md))
5. Assemble everything when the enclosure arrives

---

**Want to modify the design?** See [CUSTOMIZATION_GUIDE.md](CUSTOMIZATION_GUIDE.md)

**Need help with 3D printing?** Check [3D_PRINTING_TIPS.md](3D_PRINTING_TIPS.md)

See also: [Wiring Diagram](wiring.md), [Soldering](../assembly/soldering.md), [Final Testing](../assembly/final-testing.md)
