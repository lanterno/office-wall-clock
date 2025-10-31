# Breadboard Prototype

Assemble a no-solder prototype to validate wiring and firmware.

## Connections
- ESP32 3.3V → LED +5V (if using 5V level, prefer external 5V)
- ESP32 GND → LED GND
- GPIO2 → LED DIN via 330Ω resistor
- GPIO9 → Button (to GND); enable internal pull-up

## Steps
1. Place ESP32 and LED strip on breadboard
2. Wire power rails; add 1000µF cap across LED 5V/GND
3. Connect data line with 330Ω series resistor
4. Wire button to GPIO9 and GND
5. Flash test firmware

## Verification
- Toggle button: state changes in Serial Monitor
- LEDs animate as expected
- No flicker/brownouts during animations

---

Next: [Soldering](soldering.md)