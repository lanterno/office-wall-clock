# Wiring Diagram

Connections between ESP32-C3, button, LED strip, charger, and battery.

## Summary
- Microcontroller: ESP32-C3 DevKit
- LEDs: WS2812B (8 pixels)
- Button: SPDT or latching toggle
- Power: 3.7V LiPo via TP4056 to 3.3V regulator

## Pin Mapping

| Function | ESP32-C3 Pin | Notes |
|---------|--------------:|------|
| LED Data | GPIO 2 | Connect to DIN of WS2812B via 330Ω resistor |
| Button | GPIO 9 | Use pull-up; button to GND |
| Charger Status (optional) | GPIO 3 | Read charging state |
| Battery Voltage (optional) | GPIO 4 (ADC) | Via divider 100k/220k |

## Power
- Battery (3.7V LiPo) → TP4056 Charger → 5V USB-C input
- Output to AMS1117-3.3 (or onboard regulator) → ESP32 3.3V
- LED strip powered at 5V if available; else 3.3V logic level often works
- Common GND for all components

## Schematic Notes
- Add 1000 µF capacitor across LED power near strip
- Add 330 Ω resistor in series with LED data line
- Keep LED ground and data wire short and twisted if possible

## Assembly Order
1. Wire power rails and verify 3.3V/5V
2. Connect LED strip (5V, GND, DIN)
3. Connect button to GPIO with pull-up
4. Optional: voltage divider for battery sensing
5. Tidy cables and strain relief

## Testing
- Flash LED blink test
- Verify button reads HIGH/LOW correctly
- Confirm no brownouts when LEDs animate

---

Reference: [Specifications](specifications.md), [Soldering](../assembly/soldering.md)