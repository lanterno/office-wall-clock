# Usage Guide

**Daily operation of your Wall Clock In Machine**

## Quick Start

### Your First Day

**Morning - Arriving at Office**:
1. Toggle button **down** (or to ON position)
2. Status LED turns **green** ✅
3. Energy meter shows **7 LEDs lit** (8 hours remaining)
4. That's it! You're clocked in.

**Evening - Leaving Office**:
1. Toggle button **up** (or to OFF position)
2. Status LED turns **red** 🔴
3. Energy meter turns off
4. If you worked 8+ hours: 🎉 **Rainbow celebration!**

**That's literally it.** 2 seconds, twice a day.

---

## LED Indicator Reference

### Status LED (First LED)

| Color | Meaning | What to Do |
|-------|---------|------------|
| 🔴 **Red** (solid) | Clocked out, idle | Press button to clock in |
| 🟢 **Green** (solid) | Clocked in, working | Press button to clock out |
| 🔵 **Blue** (pulsing) | Connecting to WiFi or API | Wait 5-10 seconds |
| 🟡 **Yellow** (blinking) | API error, can't communicate | Check WiFi, see troubleshooting |
| 🟣 **Purple** (breathing) | Charging battery | Leave plugged in |
| ⚪ **White** (slow blink) | Configuration mode | Connect to WiFi hotspot to configure |

### Energy Meter (Next 7 LEDs)

Shows remaining work hours when clocked in:

```
┌──────────────────────────────────────┐
│ 8-7 hours left:  🟢🟢🟢🟢🟢🟢🟢        │  Full energy!
│ 6-5 hours left:  🟢🟢🟢🟢🟢            │  Cruising along
│ 4-3 hours left:  🟡🟡🟡🟡              │  Halfway there
│ 2-1 hours left:  🔴🔴                  │  Almost done!
│ 0 hours left:    🌈 RAINBOW! 🌈        │  You did it! 🎉
└──────────────────────────────────────┘
```

**Updates every 5 minutes** while working.

---

## Typical Usage Patterns

### Standard Office Day (8 hours)

```
08:00 AM  →  Arrive at office, toggle button ON
              Status: Green, Energy: 7 LEDs

12:00 PM  →  Lunch break (leave button ON)
              Status: Green, Energy: 4 LEDs

05:00 PM  →  Leave office, toggle button OFF
              Status: Rainbow then Red, Energy: Off
```

**Note**: Device keeps running during lunch. If you want to pause:
- Toggle OFF for lunch
- Toggle ON when returning
- Device tracks multiple sessions

### Split Day (Morning + Afternoon)

```
08:00 AM  →  Clock in (morning shift)
12:00 PM  →  Clock out (lunch break)
01:00 PM  →  Clock in (afternoon shift)  
05:00 PM  →  Clock out (end of day)
```

Each button press creates a separate time entry in your API.

### Work From Home Day

```
09:00 AM  →  Clock in from home office
05:30 PM  →  Clock out

(Battery lasts weeks without charging)
```

### Remote/Mixed Work

Device works anywhere with your WiFi or mobile hotspot!

---

## Advanced Features

### Long Press Functions

**Hold button for 5 seconds**:
- Enters **configuration mode** (white LED)
- Creates WiFi hotspot: "WallClockIn-Setup"
- Use to change WiFi or API settings

**During boot, hold button**:
- Skips WiFi connection
- Goes straight to config mode
- Useful when WiFi not available

### Battery Management

**Charging**:
- Plug in USB-C cable anytime
- Purple LED indicates charging
- Blue LED when fully charged
- Can use while charging

**Battery Life**:
- Normal use: **10-14 days** per charge
- Heavy use: **7-10 days**
- Standby (not used): **30+ days**

**Low Battery Warning**:
- Yellow LED blinks when <10%
- Plug in soon!

**Checking Battery Level**:
```bash
# Via serial monitor
pio device monitor

# Look for:
[INFO] Battery: 87% (3.92V)
```

### Power Saving

**When clocked out**:
- Device enters deep sleep (5µA)
- Wakes instantly on button press
- Saves battery dramatically

**When clocked in**:
- Stays awake to update energy meter
- Goes to light sleep between updates
- Uses ~15mA average

### Offline Operation

**If WiFi unavailable**:
1. Device stores state locally
2. Yellow LED indicates no connection
3. When WiFi returns, syncs automatically
4. Your time is not lost!

**If API unavailable**:
- Same behavior as WiFi offline
- Stores timestamps locally
- Retries API calls periodically

---

## Daily Routine Tips

### Morning Checklist

✅ Arrive at desk  
✅ Put down bag/coat  
✅ **Toggle button ON** ← 2 seconds  
✅ Boot computer  
✅ Make coffee  

**Total extra time**: 2 seconds (vs 15 seconds typing curl command!)

### Evening Checklist

✅ Finish last task  
✅ Close applications  
✅ **Toggle button OFF** ← 2 seconds  
✅ Grab belongings  
✅ Head home  

### Forgetting to Clock Out?

**No problem!** Options:

**Option 1**: Manual correction via API
```bash
# Update end time via API
curl -X PATCH https://api.example.com/api/beats/12345 \
  -d '{"stopped_at": "2025-10-29T17:00:00Z"}'
```

**Option 2**: Clock out remotely via web interface (if your API has one)

**Option 3**: Just clock out next morning and note the time

### Forgetting to Clock In?

**Option 1**: Clock in late, note actual arrival time, correct via API

**Option 2**: Create manual entry via API:
```bash
curl -X POST https://api.example.com/api/timer/start \
  -d '{"project_id": "office-time", "started_at": "2025-10-29T08:00:00Z"}'
```

---

## Maintenance

### Weekly

- Wipe LED window with microfiber cloth (if dusty)
- Charge overnight if needed

### Monthly

- Check toggle switch tightness
- Clean USB-C port if dirty (compressed air)
- Review battery runtime

### Every 6 Months

- Update firmware to latest version
- Check for loose screws in enclosure
- Verify API credentials still valid

### Annually

- Consider battery replacement if runtime <5 days
- Check all solder joints for cracks
- Update WiFi credentials if changed

---

## Troubleshooting During Use

### Button Press Not Responding

**Symptoms**: Press button, nothing happens

**Quick Checks**:
1. Is device powered on? (any LED lit?)
2. Is it in config mode? (white LED = exit config mode first)
3. Try pressing firmly
4. Check serial monitor for errors

**Solutions**:
- Power cycle device
- Check battery level
- Verify firmware running (connect to serial)

### LEDs Not Lighting Up

**Symptoms**: Status LED works, but energy meter doesn't

**Possible Causes**:
- Not clocked in yet (only shows when working)
- LEDs disabled in settings
- Hardware issue

**Solutions**:
- Clock in and wait 5 minutes
- Check LED brightness setting (may be set to 0)
- Test LEDs via serial commands

### WiFi Keeps Disconnecting

**Symptoms**: Blue LED pulses frequently, connection drops

**Causes**:
- Weak signal
- Router issues
- Power saving too aggressive

**Solutions**:
1. Move device closer to router or use extender
2. Reserved IP address for device in router
3. Disable WiFi power saving in router
4. Update firmware with fixes

### API Calls Failing

**Symptoms**: Yellow LED after button press

**Check**:
1. Is API server running?
2. Token still valid?
3. Network connectivity OK?
4. Serial monitor shows specific error

**Solutions**:
- Test API with curl command
- Verify token hasn't expired
- Check firewall rules
- Review API logs

---

## Best Practices

### DO:

✅ Charge device weekly (or when LED indicates low battery)  
✅ Keep device on desk in consistent location  
✅ Press button immediately when arriving/leaving  
✅ Clean LED window monthly  
✅ Update firmware when available  
✅ Keep API token secure  

### DON'T:

❌ Leave device in hot car (battery damage)  
❌ Submerge in water (not waterproof!)  
❌ Drop from height (electronics are fragile)  
❌ Pull USB cable at an angle (damages port)  
❌ Forget to charge for months (deep discharge damages battery)  
❌ Share API credentials  

---

## Integrations & Workflows

### With Your Timer API

The device integrates seamlessly with your existing timer backend:

**Your API can**:
- Generate reports from device data
- Calculate work hours automatically
- Send notifications (email when you forgot to clock out)
- Integrate with payroll systems
- Track productivity trends

**Example Workflow**:
```
Device → API → Database → Analytics Dashboard
                        → Payroll System
                        → Email Reports
```

### With Other Tools (via API)

**Zapier/IFTTT**:
- Clock in → Start focus music on Spotify
- Clock out → Send summary to Slack
- Battery low → SMS notification

**Home Automation**:
- Clock in → Turn on desk lamp (IFTTT + smart plug)
- Clock out → Lock office door (smart lock API)

**Calendar Integration**:
- Sync clock in/out times to Google Calendar
- Block focus time based on work hours

---

## Tips & Tricks

### Placement Optimization

**Best locations**:
- Corner of desk (easy to reach)
- Near keyboard (within arm's length)
- Away from coffee cup (avoid spills!)
- Not blocking monitor

### Energy Meter as Motivator

- Green LEDs = plenty of time, relax
- Yellow LEDs = focus mode activated
- Red LEDs = almost done, push through!
- Rainbow = celebrate! 🎉

### Battery Life Maximization

**To extend battery life**:
1. Reduce LED brightness (in config)
2. Enable deep sleep (default)
3. Charge to 80% instead of 100% (longer battery lifespan)
4. Store at 50% charge if not using for weeks

### Custom Hacks

**Ideas from the community**:
- Add second button for "break" mode
- Connect buzzer for audio feedback
- Add OLED display showing time remaining
- 3D print custom enclosure designs
- Program custom LED animations

Share your hacks on GitHub!

---

## FAQ

**Q: Can I use this for multiple jobs/projects?**  
A: Currently tracks one project. Modify `PROJECT_ID` in firmware for different projects, or add project selection feature.

**Q: Does it work without internet?**  
A: Needs WiFi for API calls. Stores state locally if connection lost, syncs when reconnected.

**Q: Can multiple people use devices with same API?**  
A: Yes! Each device sends its own timer entries. Make sure each has unique identifier in API.

**Q: What if I work >8 hours?**  
A: Energy meter goes to 0, but device keeps tracking. Change `WORK_HOURS` in config for different default.

**Q: Can I check my time from phone?**  
A: Device doesn't have app, but you can check via your API's web interface or mobile app.

**Q: Is my data secure?**  
A: Device uses HTTPS for API calls. Data security depends on your API backend implementation.

**Q: Can I turn off LED animations?**  
A: Currently no, but you can reduce brightness to minimum. Feature request welcome!

---

## Getting Help

**Issue with device?**
1. Check [Troubleshooting Guide](TROUBLESHOOTING.md)
2. Review serial monitor logs
3. Test API separately with curl
4. Open GitHub issue with logs

**Feature request?**
- Open GitHub issue with "enhancement" label
- Describe use case
- Vote on existing requests

**Bug found?**
- Open GitHub issue with "bug" label
- Include firmware version
- Attach serial logs
- Describe steps to reproduce

---

## Enjoy Your Device! 🎉

You've saved yourself from typing curl commands forever!

**Time saved per year**: ~2.6 hours  
**Satisfaction**: Priceless 😊

**Share your experience**:
- Tweet @yourusername with #WallClockInMachine
- Post photo on r/arduino or r/homeautomation
- Write blog post about your build
- Contribute improvements via GitHub PR

---

**Happy tracking! 📊✨**
