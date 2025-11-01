# Final Testing

Checklist to validate a finished device.

## Functional
- Button toggles states reliably (10 cycles)
- Status LED reflects state transitions
- Energy meter increments each hour (simulate fast mode if available)
- WiFi connects and API calls succeed

## Power
- Battery charges from 20% to 100% without overheating
- No brownouts during peak LED animation
- Idle current low in standby

## Mechanical
- Enclosure closes flush with no pinched wires
- Button feels crisp; LEDs evenly diffused
- USB-C cable fits without strain

## Firmware
- Configuration saved across reboots
- Time sync works; timestamps correct
- Logs are clean (no repeated errors)

---

If any item fails, check the component specifications and wiring connections.