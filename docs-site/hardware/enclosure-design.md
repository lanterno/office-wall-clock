# Enclosure Design

Design guidelines, dimensions, and options for the Wall Clock In Machine enclosure.

## Goals
- Clean, compact desktop form factor
- One main button on top/front
- LEDs visible from typical seating position
- Easy access to USB-C charging
- Safe mounting for battery

## Recommended Dimensions
- Overall: 100 x 60 x 35 mm (W x D x H)
- Button hole: 16 mm (for panel-mount button)
- LED window: 8 x 70 mm light strip diffuser
- USB-C cutout: 9 x 6 mm

## Materials
- 3D printed PLA or PETG (2 mm walls)
- Acrylic diffuser for LEDs (1-2 mm)
- Brass heat inserts for screws (M3)

## Layout
```
[ Button ]   [ LED window ]

[ ESP32 ] [ Battery ] [ Charger ]  (inside, mounted on standoffs)
```

## Mounting
- Use M3 standoffs (8-12 mm) for the ESP32 board
- Battery secured with Velcro and a strap
- Cable management using adhesive tie mounts

## 3D Printing
- Layer height: 0.2 mm
- Infill: 20-30%
- Supports: For USB-C cutout and button hole as needed
- Print time: 3-5 hours depending on printer

## Assembly Order
1. Insert brass heat inserts into bottom shell
2. Mount ESP32 and charger board
3. Place LED strip and diffuser
4. Route wiring; test electronics
5. Secure battery
6. Close top shell; install button

## Alternatives
- Laser-cut acrylic sandwich design
- Off-the-shelf plastic project box (Hammond 1551 series)
- Wooden enclosure for premium look

## Files and Models
- STL/STEP: Coming soon (to be added under `hardware/enclosure/`)

---

See also: [Wiring Diagram](wiring.md), [Soldering](../assembly/soldering.md), [Final Testing](../assembly/final-testing.md)