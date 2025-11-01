# LED Indicators

This page explains all LED patterns and what they mean on the Wall Clock In Machine.

## LED Layout

- 1x Top Status LED (WS2812 pixel 0)
- 7x Energy Meter LEDs (WS2812 pixels 1-7)
- 1x Charger LED (on charging module, red/green)

## Top Status LED (Pixel 0)

| Pattern | Meaning | Action |
|--------|---------|--------|
| Breathing Green | Clocked out, idle | None |
| Solid Blue | Clocked in, working | None |
| Pulsing Blue (5s) | Sync in progress | Wait |
| Fast Rainbow | WiFi setup mode (AP) | Connect via captive portal |
| Blinking Yellow (2 Hz) | Battery low (<20%) | Charge soon |
| Blinking Red (2 Hz) | Error state | See Troubleshooting |
| Off | Deep sleep | Press button or power cycle |

## Energy Meter LEDs (Pixels 1-7)

- Fill from left to right as hours accumulate
- Color gradient indicates progress
  - 1-2 LEDs: Green
  - 3-4 LEDs: Yellow
  - 5-6 LEDs: Orange
  - 7 LEDs: Red
- Fades out on clock out

## Charger LED

- Red: Charging
- Green: Fully charged
- Off: Not connected or no battery

## Setup Mode Animation

When device boots with button pressed (or no saved WiFi):

1. Top LED shows fast rainbow cycle
2. Energy meter LEDs scroll left-right
3. Device exposes WiFi AP: `WALL-CLOCK-SETUP`
4. Connect to AP, then configure WiFi and API endpoint

## Error Patterns

### API Error
- Top LED: Blinking Red
- Energy LEDs: Off
- Action: Check API URL and network connectivity

### WiFi Error
- Top LED: Blue pulse every 2 seconds
- Energy LEDs: Single yellow blink
- Action: Move closer to router, re-enter credentials

### Sensor/Button Error
- Top LED: Alternating red/orange
- Energy LEDs: All dim red
- Action: Check button wiring and debounce settings

## Customization

You can customize colors and patterns in firmware:

- File: `firmware/src/led_controller.cpp`
- Constants to change:
  - `STATUS_COLOR_WORKING`
  - `STATUS_COLOR_IDLE`
  - `COLOR_GRADIENT[]`
  - `BRIGHTNESS`

Example (pseudocode):

```cpp
setStatusColor(working ? Blue : Green);
fillEnergyMeter(hoursWorked, gradient);
if (syncing) pulse(StatusPixel, Blue);
```

## Tips

- Keep brightness at 25-50% for comfortable desk viewing
- Avoid direct sunlight for accurate color perception
- Clean LED diffuser monthly for consistent light

---

See also: [Daily Operation](daily-operation.md), [Battery Management](battery.md)