# Daily Operation

This guide covers the everyday use of your Wall Clock In Machine for tracking office work hours.

## Basic Operation

### Starting Your Work Day

**When you arrive at the office:**

1. **Check Device Status**
   - Top LED should be breathing green (clocked out, idle)
   - If red: Check battery level and power connections
   - If blinking blue: Device is connecting to WiFi

2. **Clock In**
   - Press button **down** (toggle to "working" position)
   - Top LED turns solid blue
   - Energy meter fills 1 LED (green) after ~1 hour

3. **Confirmation**
   - Listen for quiet "beep" from LED feedback (visual pulse)
   - Check backend API to verify session started
   - If no response: Check WiFi connection and API configuration

**Normal behavior**: Button stays in DOWN position throughout your work session.

### During Your Work Session

**Energy Meter Visualization:**

The 7 lower LEDs show your accumulated work time:

| Hours Worked | LEDs Lit | Color Gradient |
|-------------|----------|----------------|
| 0-1 hour | 1 LED | Green |
| 1-2 hours | 2 LEDs | Green |
| 2-3 hours | 3 LEDs | Green-Yellow |
| 3-4 hours | 4 LEDs | Yellow |
| 4-5 hours | 5 LEDs | Yellow-Orange |
| 5-6 hours | 6 LEDs | Orange-Red |
| 6+ hours | 7 LEDs | Red (full) |

**Color meanings:**
- **Green (0-2 hours)**: Fresh, starting work
- **Yellow (2-4 hours)**: Productive middle
- **Orange (4-5 hours)**: Consider a break
- **Red (5+ hours)**: Long session, time for lunch/break!

**Status LED (top):**
- **Solid Blue**: Working normally, clocked in
- **Pulsing Blue**: Sending API update (every 5 minutes)
- **Blinking Yellow**: Battery below 20%
- **Blinking Red**: Error (check battery level and connections)

### Taking Breaks

**The Wall Clock In Machine tracks continuous work time:**

**Option 1: Keep Running** (Recommended for short breaks)
- Leave button DOWN
- Take coffee/bathroom break (5-15 min)
- Energy meter continues counting
- No action needed

**Option 2: Clock Out for Breaks** (Lunch, meetings)
- Press button **up** (toggle to "stopped" position)
- Device saves session and uploads to API
- Take your break
- Press button **down** when you return to start new session

**Why Option 1 is better:**
- One continuous session = accurate daily total
- Less manual interaction
- Backend API aggregates all sessions automatically

**When to use Option 2:**
- Lunch break (30+ minutes)
- Off-site meeting
- End of work day

### Ending Your Work Day

**When leaving the office:**

1. **Clock Out**
   - Press button **up** (toggle to "clocked out" position)
   - Top LED pulses blue (uploading session)
   - Energy meter LEDs fade out one by one
   - Top LED returns to breathing green

2. **Verification**
   - Check backend API/dashboard for recorded hours
   - Verify session end time is correct
   - Review energy meter accuracy (should match your actual hours)

3. **Charging** (if needed)
   - Plug in USB-C cable if battery below 30%
   - Charging LED turns red
   - Unplug when green (or leave overnight)

**Battery management**: See [Battery Management](battery.md)

## LED Indicator Reference

### Quick Status Check

| Indicator | Pattern      | Meaning                      | Action               |
|-----------|--------------|------------------------------|----------------------|
| Top LED   | Solid Blue   | Connecting to WiFi           | Wait a few seconds   |
| Top LED   | Solid Green  | Connected / last API OK      | Normal operation     |
| Top LED   | Solid Yellow | WiFi / API error (last call) | Check WiFi + backend |
| Top LED   | Purple       | API call in progress         | Wait; turns green    |
| Energy Meter | Green→Yellow gradient | Relative “work energy” / progress | Visual only |

For detailed LED meanings, see [LED Indicators](led-indicators.md).

## Common Usage Patterns

### Pattern 1: Standard 9-5 Office Day

```
08:45 - Arrive at office
        - Device in standby (green breathing)
        - Press button DOWN
        
09:00 - Start work
        - 1 green LED lit
        
12:00 - Lunch break (press button UP)
        - Session 1 saved: 3 hours
        - Device back to standby
        
13:00 - Return from lunch
        - Press button DOWN
        - New session starts
        
17:00 - End work day (press button UP)
        - Session 2 saved: 4 hours
        - Total: 7 hours recorded
```

### Pattern 2: Long Single Session

```
09:00 - Clock in (button DOWN)
10:00 - 1 LED (green)
11:00 - 2 LEDs (green)
12:00 - 3 LEDs (green-yellow) - Quick desk lunch, stay clocked in
13:00 - 4 LEDs (yellow)
14:00 - 5 LEDs (orange)
15:00 - 6 LEDs (orange-red)
16:00 - 7 LEDs (red) - Full meter!
17:00 - Clock out (button UP)
        - Single 8-hour session saved
```

### Pattern 3: Flexible Remote Work

```
10:00 - Start work (button DOWN)
11:30 - Break (button UP) - 1.5 hours saved
14:00 - Resume (button DOWN)
16:00 - Short break - Leave button DOWN
16:15 - Continue working
18:30 - End (button UP) - 4.5 hours saved
        - Total: 6 hours
```

## Battery Behavior

### Expected Battery Life

**Normal usage** (clocked in 6-8 hours/day):
- **Fresh charge**: 10-14 days between charges
- **Year 2**: 8-12 days
- **Year 3**: 6-10 days

**LED brightness impact:**
- 100% brightness: 7-10 days
- 50% brightness: 12-16 days
- 25% brightness: 16-20 days

**Power-saving mode** (deep sleep when clocked out):
- Standby power: ~5 µA
- Working power: ~80-150 mA
- WiFi sync: ~200 mA peak (every 5 min for 2-5 seconds)

### Charging Habits

**Best practices:**
- Charge when battery drops below 20% (yellow warning)
- Overnight charging is fine (charger has auto-cutoff)
- Unplug at 100% to maximize battery lifespan
- Charge every weekend if you use daily

**Avoid:**
- Letting battery fully drain (below 5%)
- Keeping plugged in 24/7
- Charging in direct sunlight or hot environments

See detailed charging guide: [Battery Management](battery.md)

## API Integration

### Backend Communication

**Automatic sync schedule:**
- **Clock in**: Immediate POST to start session
- **During session**: Status ping every 5 minutes (optional)
- **Clock out**: Immediate POST to end session with duration

**API endpoints used:**
```
POST /api/beats/start   # Clock in
POST /api/beats/end     # Clock out
GET  /api/beats/status  # Optional health check
```

**Network resilience:**
- Device stores session locally if offline
- Auto-retry up to 3 times with exponential backoff
- Syncs when WiFi returns
- No data loss even if network fails

### Checking Your Data

**Via Web Dashboard** (if you built one):
1. Open backend dashboard URL
2. View daily/weekly/monthly summaries
3. Export CSV for invoicing or records

**Via Direct API Query:**
```bash
curl -X GET "https://your-api.com/api/beats?date=2024-01-15" \
  -H "Authorization: Bearer YOUR_TOKEN"
```

**Data stored:**
- Session start timestamp
- Session end timestamp
- Duration (calculated)
- Device ID (your ESP32 MAC address)
- Project ID (if configured)

## Troubleshooting Quick Checks

### Button Press Not Responding
1. Check battery level (yellow/red LED?)
2. Try long press (2 seconds)
3. Check button physical connection
4. Check hardware connections and battery level

### Session Not Recorded
1. Check WiFi connection (blue blinking = connecting)
2. Verify API endpoint in configuration
3. Check backend API logs
4. Check WiFi connection and API configuration

### Wrong Duration Recorded
1. Verify clock-out button press registered
2. Check for automatic session timeout (default: 12 hours)
3. Review API timestamp accuracy
4. Check device time sync (NTP)

### LEDs Not Turning On
1. Check battery charge
2. Verify LED power connection
3. Test with USB-C power
4. Check hardware connections and battery level

## Advanced Usage

### Multiple Devices

**If you have multiple work locations:**

1. Build one device per location
2. Configure each with unique device ID
3. Backend API tracks all devices
4. Dashboard shows combined total

**Example:**
- Device A: EPFL office
- Device B: Home office
- Device C: Co-working space
- All sync to same backend account

### Project Tracking

**If your backend supports projects:**

1. Configure project ID in firmware
2. Use button patterns for project switching:
   - Single click: Default project
   - Double click: Alternate project (requires firmware mod)
   - Long press (5s): Admin mode

3. Or use physical DIP switches for 4-8 projects

### Offline Mode

**Device works offline:**
- Sessions stored in ESP32 EEPROM
- Holds up to 50 sessions (configurable)
- Auto-sync when WiFi returns
- LED shows orange status indicator

**Activate offline mode:**
- Long press button (10 seconds) at startup
- Top LED turns orange
- All sessions cached locally

**Sync later:**
- Connect to WiFi
- Long press button (10 seconds) again
- Device uploads all cached sessions

## Maintenance Schedule

### Daily
- ✓ Observe LED indicators for abnormal behavior
- ✓ Verify sessions recorded correctly

### Weekly
- ✓ Check battery level (charge if needed)
- ✓ Wipe dust from button and enclosure
- ✓ Review backend data for accuracy

### Monthly
- ✓ Clean LED surface with microfiber cloth
- ✓ Check button feel (should have crisp click)
- ✓ Verify WiFi connection strength
- ✓ Update firmware if new version available

### Yearly
- ✓ Deep clean enclosure interior
- ✓ Check solder joints for cold joints
- ✓ Test battery capacity (may need replacement after 3-5 years)
- ✓ Re-flash firmware to latest version

See full maintenance guide: [Maintenance](maintenance.md)

## Tips & Tricks

### Improving Accuracy
- Place device away from electromagnetic interference
- Use stable WiFi network (not guest networks)
- Configure NTP server for accurate timestamps
- Test button before each work week

### Reducing Distractions
- Lower LED brightness during focus work
- Disable energy meter animation (keep only top status LED)
- Use minimal brightness at night
- Turn off status beeps

### Extending Battery Life
- Reduce LED brightness to 25%
- Disable WiFi sync during sessions (sync only at clock-out)
- Use deep sleep modes aggressively
- Charge every weekend preventively

### Making It Fun
- Customize LED colors per project
- Add achievement animations (1000 hours, etc.)
- Share weekly stats with team
- Gamify productivity with LED effects

## Next Steps

- Learn about [LED Indicators](led-indicators.md) in detail
- Understand [Battery Management](battery.md)
- Review [Maintenance](maintenance.md) procedures

---

**Questions?** Check the documentation or open an issue on GitHub!
