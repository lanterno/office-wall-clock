# Battery Management

Guidance to keep your device healthy and extend battery life.

## Specs

- 3.7V LiPo, 2000 mAh
- Charger: TP4056 (USB-C module)
- Runtime: 10-14 days typical

## Charging

- Plug into USB-C 5V source (phone charger is fine)
- Red LED on charger = charging, Green = full
- Safe to leave overnight (auto cutoff)

### Best Practices
- Charge around 20-30% (yellow warning)
- Unplug when fully charged
- Avoid full discharge (<5%)
- Don’t leave on charger for weeks

## Battery Life vs Brightness

| Brightness | Typical Days |
|-----------:|--------------:|
| 25% | 16-20 |
| 50% | 12-16 |
| 100% | 7-10 |

Adjust in firmware: `BRIGHTNESS` constant in `led_controller.cpp`.

## Replacement

Expected lifespan: 3-5 years.

Signs you need a replacement:
- Device dies quickly after charge
- Charger stays red unusually long
- Battery swollen or warm (stop using immediately)

Steps:
1. Buy replacement 3.7V LiPo (same dimensions, JST-PH 2.0)
2. Power off device, disconnect old battery
3. Connect new battery paying attention to polarity
4. Charge fully before first use

## Storage

If not using for 1+ month:
- Charge to ~50-70%
- Power off and disconnect from charger
- Store at 15-25°C, dry place
- Recharge every 3 months

## Safety

- Never puncture or bend the cell
- Don’t short-circuit terminals
- Use quality chargers only
- Stop using if battery swells, smells, or overheats

## Troubleshooting

- Charges but dies fast → Battery aging; reduce brightness; consider replacement
- Doesn’t charge → Check USB cable and charger; verify polarity; inspect TP4056 module
- Gets hot while charging → Unplug immediately; inspect for short; replace battery

---

Related: [LED Indicators](led-indicators.md), [Power Problems](../troubleshooting/power.md), [Maintenance](maintenance.md)