# Component Testing

Verify each part works before final assembly.

## ESP32-C3
- Upload blink sketch
- Open Serial Monitor @ 115200
- Verify reset and boot messages

## LED Strip
- Connect 5V/GND and DIN via 330Ω
- Run simple Rust LED test (smart-leds example)
- Check all 8 pixels light in order

## Button
- Wire to GPIO with pull-up
- Read pin state while toggling
- Debounce: verify stable transitions

## Charger & Battery
- Check TP4056 LEDs: red (charging) → green (full)
- Measure battery voltage: 3.7–4.2V

## Troubleshooting
- No serial? Try different cable/port
- Random LED colors? Ground/data integrity; add large cap
- Button bounces? Increase debounce ms in firmware

---

Next: [Breadboard Prototype](breadboard.md)