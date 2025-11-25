# LED Indicators

This page explains all LED patterns and what they mean on the Wall Clock In Machine.

## LED Layout

- 1x Top Status LED (WS2812 pixel 0)
- 7x Energy Meter LEDs (WS2812 pixels 1-7)
- 1x Charger LED (on charging module, red/green)

## Top Status LED (Pixel 0)

The current Rust firmware uses **simple solid colors**:

| Pattern      | Meaning                      | Action                |
|-------------|------------------------------|-----------------------|
| Solid Blue  | Connecting to WiFi           | Wait a few seconds    |
| Solid Green | Connected / last API OK      | Normal operation      |
| Solid Yellow| WiFi / API error (last call) | Check WiFi + backend  |
| Purple      | API call in progress         | Wait; turns green/end |
| Off         | Powered off / not running    | Check power/USB       |

Fast rainbow animation is currently used as a **demo/config placeholder** on
long‑press and does not start a WiFi setup portal yet.

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

## Setup / Demo Animation

When you long‑press the button, the firmware triggers a rainbow animation on all
LEDs. This is currently just a **visual demo** and a placeholder for future
configuration modes.

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

- File: `firmware/src/tasks/led.rs`
- Enum: `StatusColor` (Red, Green, Blue, Yellow, Purple, Off)
- Match on `LedCommand` in `led_task` to change how LEDs respond to events.

## Tips

- Keep brightness at 25-50% for comfortable desk viewing
- Avoid direct sunlight for accurate color perception
- Clean LED diffuser monthly for consistent light

---

See also: [Daily Operation](daily-operation.md), [Battery Management](battery.md)