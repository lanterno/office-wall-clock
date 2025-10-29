# Troubleshooting Guide

**Common issues and solutions for the Wall Clock In Machine**

## Quick Diagnostic Flowchart

```
Device not responding?
├─ No LED lit at all?
│  ├─ Yes → Check POWER issues (Section 1)
│  └─ No → LED lit? Continue...
│
├─ Yellow LED blinking?
│  ├─ Yes → Check API/NETWORK issues (Section 2)
│  └─ No → Continue...
│
├─ Button not working?
│  ├─ Yes → Check BUTTON issues (Section 3)
│  └─ No → Continue...
│
├─ WiFi not connecting?
│  └─ Yes → Check WIFI issues (Section 4)
│
└─ Everything powers on but doesn't work?
   └─ Check FIRMWARE issues (Section 5)
```

---

## Section 1: Power Issues

### Problem: No LEDs Light Up

**Possible Causes**:
- Battery dead/disconnected
- Power switch off
- Hardware failure
- Firmware not loaded

**Diagnostic Steps**:

1. **Check battery voltage**:
   ```bash
   # Multimeter on battery connector
   # Should read 3.0V - 4.2V
   # < 3.0V = dead battery
   ```

2. **Check USB power**:
   - Plug in USB-C cable
   - TP4056 should have LED (red=charging, blue=done)
   - If no TP4056 LED → charger module dead or bad cable

3. **Check connections**:
   - Battery connector properly seated?
   - Wires from TP4056 OUT+ and OUT- connected?
   - ESP32 getting power? (measure 3.3V on 3.3V pin)

4. **Bypass test**:
   - Connect USB directly to ESP32 (3.3V/5V pin)
   - If ESP32 boots → Power circuit issue
   - If still nothing → ESP32 may be dead

**Solutions**:

| Symptom | Solution |
|---------|----------|
| Battery voltage < 3.0V | Charge battery for 3+ hours, replace if won't charge |
| No TP4056 LED when plugged | Replace TP4056 module or USB cable |
| ESP32 doesn't boot on USB power | Re-flash firmware or replace ESP32 |
| Voltage present but no boot | Check reset circuit, shorting RST to GND briefly |

### Problem: Device Powers Off Randomly

**Possible Causes**:
- Loose battery connection
- Brownout (voltage too low)
- Software crash

**Solutions**:

1. **Secure battery connector**:
   - Re-seat JST connector
   - Add drop of hot glue for strain relief

2. **Check voltage under load**:
   ```bash
   # Monitor battery voltage while LEDs on
   # Should stay > 3.0V
   # Drops below 3.0V = weak battery or bad connection
   ```

3. **Enable brownout detector logs**:
   ```cpp
   // In main.cpp setup():
   esp_register_shutdown_handler(&logShutdownReason);
   ```

4. **Add more capacitance**:
   - 100µF capacitor near ESP32 power pins
   - Helps with voltage spikes

---

## Section 2: Network & API Issues

### Problem: Yellow LED (API Error)

**What device is trying to do**:
1. Connect to WiFi ✅
2. Make HTTP/HTTPS request to API ❌ (failing here)

**Check serial monitor first**:
```bash
pio device monitor --baud 115200

# Look for specific error:
[ERROR] HTTP error: 401  → Authentication problem
[ERROR] HTTP error: 404  → Wrong endpoint
[ERROR] HTTP error: 500  → API server error
[ERROR] Connection failed → Network/SSL issue
[ERROR] Timeout → API too slow
```

**Common HTTP Error Codes**:

| Code | Meaning | Solution |
|------|---------|----------|
| **401** | Unauthorized | Check API token, update in config |
| **403** | Forbidden | API token doesn't have permissions |
| **404** | Not Found | Verify API endpoint path in firmware |
| **429** | Too Many Requests | Wait 1 minute, API rate limited |
| **500** | Server Error | Check your API backend logs |
| **502/503** | Service Unavailable | API server down, wait or restart it |

**Testing API Manually**:

```bash
# Test from computer on same network
curl -v -X POST https://your-api.com/api/timer/start \
  -H "Content-Type: application/json" \
  -H "Authorization: Bearer your_token" \
  -d '{"project_id": "office-time"}'

# Check:
# - Does it work from computer?
# - What response code?
# - Any error messages?
```

**Solutions**:

1. **401/403 Errors**:
   ```bash
   # Re-enter correct API token
   # Long-press button → Config mode
   # Update token via web portal
   ```

2. **404 Errors**:
   - Verify API paths in `firmware/src/api_client.cpp`
   - Ensure paths match your API documentation
   - Re-compile and upload firmware

3. **SSL/Certificate Errors**:
   ```cpp
   // In api_client.cpp, we use:
   secure_client->setInsecure();
   
   // This skips certificate validation
   // If you want proper validation:
   secure_client->setCACert(your_ca_cert);
   ```

4. **Timeout Errors**:
   - API taking >10 seconds to respond
   - Increase timeout in config.h:
     ```cpp
     #define API_TIMEOUT_MS  20000  // 20 seconds
     ```

### Problem: Blue LED Pulsing (WiFi Connecting)

**Device stuck trying to connect to WiFi**

**Diagnostic**:
```bash
# Serial monitor shows:
[INFO] Connecting to WiFi: YourNetwork
[INFO] Connecting to WiFi: YourNetwork
[INFO] Connecting to WiFi: YourNetwork
# (repeating forever)
```

**Common Causes**:

1. **Wrong WiFi password**
   - Solution: Long-press reset → Re-enter credentials

2. **5GHz network**
   - ESP32 only supports 2.4GHz
   - Solution: Connect to 2.4GHz network or enable dual-band

3. **Hidden network**
   - Solution: Manually enter SSID in config portal

4. **Special characters in password**
   - Some chars like `"` or `$` cause issues
   - Solution: Change WiFi password or escape properly

5. **MAC filtering**
   - Router blocks unknown devices
   - Solution: Add ESP32 MAC address to whitelist
   - Find MAC: Check serial monitor at boot or router admin

6. **Too far from router**
   - Weak signal
   - Solution: Move closer or use WiFi extender

7. **WPA3-only network**
   - ESP32 supports WPA2
   - Solution: Enable WPA2/WPA3 mixed mode on router

**Solutions**:

```bash
# Force config mode
# Hold button for 5 seconds → White LED

# Connect to "WallClockIn-Setup"
# Re-enter WiFi credentials carefully

# If still failing, test with phone hotspot:
# 1. Create hotspot on phone (2.4GHz, simple password)
# 2. Configure device to connect to hotspot
# 3. If works → Problem is home WiFi settings
# 4. If fails → Device hardware/firmware issue
```

### Problem: WiFi Connects Then Disconnects

**Symptoms**: Connects successfully, works for a while, then drops

**Causes**:
- Power saving too aggressive
- Router disconnects idle clients
- Weak signal causing reconnects

**Solutions**:

1. **Disable WiFi sleep** (in main.cpp):
   ```cpp
   void setup() {
     // After WiFi.begin()
     WiFi.setSleep(false);
   }
   ```

2. **Reserve IP address**:
   - In router admin, assign static IP to ESP32 MAC
   - Prevents DHCP lease expiration disconnects

3. **Keep-alive pings**:
   ```cpp
   // In loop(), ping gateway every 5 minutes
   if (millis() - lastPing > 300000) {
     WiFi.ping(WiFi.gatewayIP());
     lastPing = millis();
   }
   ```

4. **Improve signal strength**:
   - Add external antenna to ESP32
   - Move device closer to router
   - Use WiFi extender/repeater

---

## Section 3: Button Issues

### Problem: Button Press Not Detected

**Symptoms**: Press button, nothing happens, no logs

**Diagnostic**:
```bash
# Serial monitor with debug enabled
# Should see when button pressed:
[DEBUG] Button pressed
```

**Testing button hardware**:
```bash
# With multimeter in continuity mode:
# Toggle switch position 1: Common <-> Terminal 1 (beep)
# Toggle switch position 2: Common <-> Terminal 2 (beep)
# No beep = faulty switch
```

**Causes & Solutions**:

1. **GPIO not connected**:
   - Check wire from GPIO9 to switch
   - Verify solder joint not cold/broken
   - Test continuity

2. **Internal pull-up not enabled**:
   ```cpp
   // In button_handler.cpp, verify:
   pinMode(pin, INPUT_PULLUP);
   ```

3. **Switch bouncing excessively**:
   - Add external 10kΩ pull-up resistor
   - Add 0.1µF capacitor across switch terminals

4. **Wrong GPIO pin**:
   - Verify using GPIO9 (not GPIO10 or other)
   - Some GPIOs are input-only or have special functions

5. **Firmware not running**:
   - Check serial monitor for boot messages
   - If silent → firmware not loaded or crashed

**Testing in isolation**:
```cpp
// Minimal button test code
void setup() {
  Serial.begin(115200);
  pinMode(9, INPUT_PULLUP);
}

void loop() {
  int state = digitalRead(9);
  Serial.printf("Button: %d\n", state);
  delay(100);
}

// Upload this test code
// Press button and watch serial output
// Should toggle between 0 (pressed) and 1 (released)
```

### Problem: Button Triggers Multiple Times (Bouncing)

**Symptoms**: One press registers as 2-3 presses

**Cause**: Mechanical switch bounce not properly debounced

**Solutions**:

1. **Increase debounce time** (in config.h):
   ```cpp
   #define BUTTON_DEBOUNCE_MS  100  // Increase from 50 to 100
   ```

2. **Add hardware debouncing**:
   - 0.1µF capacitor across switch terminals
   - OR 10kΩ resistor + 0.1µF capacitor (RC filter)

3. **Better quality switch**:
   - Replace with higher quality toggle switch
   - Gold-plated contacts have less bounce

### Problem: Long Press Not Working

**Symptoms**: Can't enter config mode

**Cause**: Long press threshold too long or button handler issue

**Solutions**:

1. **Reduce long press time** (in config.h):
   ```cpp
   #define BUTTON_LONG_PRESS_MS  2000  // Reduce from 3000 to 2000
   ```

2. **Test explicitly**:
   ```bash
   # Serial monitor with debug:
   # Hold button and watch:
   [DEBUG] Button pressed
   # (after 3 seconds)
   [INFO] Button long press detected
   ```

3. **Use serial command instead**:
   ```bash
   # Type in serial monitor:
   config
   # Enters config mode without button
   ```

---

## Section 4: LED Issues

### Problem: No LEDs Light Up

**But status LED (first LED) works**

**Causes**:
- LED strip not powered
- DATA pin not connected
- LED strip damaged

**Testing**:

1. **Check LED power**:
   ```bash
   # Measure voltage on LED strip VCC pin
   # Should be 3.3V or 5V (depending on your wiring)
   ```

2. **Test LED strip separately**:
   ```cpp
   // Upload FastLED "Blink" example
   // Should make all LEDs blink
   // If not → LED strip hardware issue
   ```

3. **Verify DATA pin**:
   - Connected to GPIO8?
   - Check solder joint
   - Test continuity

**Solutions**:

| Issue | Fix |
|-------|-----|
| No power to LEDs | Connect LED VCC to power rail |
| Wrong DATA pin | Move wire to GPIO8 |
| Damaged LED | Replace LED strip (cheap!) |
| Voltage too low | LEDs may need 5V, add boost converter |

### Problem: LEDs Show Wrong Colors

**Symptoms**: Colors off (red shows as green, etc.)

**Cause**: Wrong color order in firmware

**Solution**:

```cpp
// In led_controller.h, try different orders:
#define COLOR_ORDER GRB  // Default
// OR
#define COLOR_ORDER RGB
// OR
#define COLOR_ORDER BGR

// Re-compile and test which looks correct
```

### Problem: Energy Meter Not Updating

**Symptoms**: Shows same LEDs even after hours pass

**Cause**: Update interval too long or time not syncing

**Diagnostic**:
```bash
# Serial monitor:
[DEBUG] Energy meter update: 6/8 hours remaining
# Should update every 5 minutes
```

**Solutions**:

1. **Force update** (in config.h):
   ```cpp
   #define ENERGY_UPDATE_INTERVAL_MS  60000  // 1 minute instead of 5
   ```

2. **Check time sync**:
   - Device uses `millis()` for relative time
   - May drift slightly (not a problem for hourly tracking)

3. **Manual test**:
   ```cpp
   // In loop(), add:
   if (Serial.available()) {
     char cmd = Serial.read();
     if (cmd == 'u') {
       updateEnergyMeter();
       Serial.println("Force updated energy meter");
     }
   }
   ```

### Problem: LEDs Too Bright/Dim

**Solution**:

```cpp
// In config.h:
#define LED_BRIGHTNESS  255  // 0-255

// For night-friendly:
#define LED_BRIGHTNESS  32   // Very dim

// For bright office:
#define LED_BRIGHTNESS  200  // Quite bright
```

---

## Section 5: Firmware Issues

### Problem: Device Boots Into Crash Loop

**Symptoms**: Rapid rebooting, serial shows crash

**Serial output**:
```
Guru Meditation Error: Core 0 panic'ed (LoadProhibited)
...
Backtrace: 0x400... 0x400...
```

**Causes**:
- Memory corruption
- Null pointer access
- Stack overflow
- Incompatible library versions

**Solutions**:

1. **Erase flash completely**:
   ```bash
   esptool.py --port /dev/cu.usbserial-110 erase_flash
   ```

2. **Re-upload firmware**:
   ```bash
   pio run --target upload
   ```

3. **Check library versions**:
   ```bash
   # In platformio.ini, use specific versions:
   lib_deps = 
       fastled/FastLED@3.6.0
       tzapu/WiFiManager@2.0.16-rc.2
   ```

4. **Enable debug**:
   ```cpp
   // In config.h:
   #define LOG_LEVEL LOG_LEVEL_DEBUG
   ```

### Problem: "Brownout Detector Was Triggered"

**Symptoms**: Device resets with this error

**Cause**: Voltage drops below threshold (usually during WiFi transmission)

**Solutions**:

1. **Add capacitance**:
   - 100µF electrolytic near ESP32 power pins
   - 10µF ceramic close to chip

2. **Better power supply**:
   - Use 5V 2A USB adapter (not computer USB)
   - Thicker power wires (reduce resistance)

3. **Reduce power consumption**:
   ```cpp
   // Reduce WiFi power:
   WiFi.setTxPower(WIFI_POWER_15dBm);
   
   // Reduce LED brightness:
   #define LED_BRIGHTNESS  64
   ```

4. **Disable brownout detector** (NOT RECOMMENDED):
   ```cpp
   // In setup():
   WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
   // Only use if you can't fix power issue
   ```

### Problem: OTA Update Fails

**Symptoms**: Can't update firmware wirelessly

**Solutions**:

1. **Check mDNS working**:
   ```bash
   # Ping device hostname
   ping wall-clock-in.local
   
   # If fails, use IP instead:
   pio run --target upload --upload-port 192.168.1.42
   ```

2. **Firewall blocking**:
   - Allow port 3232 (Arduino OTA)
   - Temporarily disable firewall to test

3. **Not enough space**:
   - OTA needs ~2x firmware size free
   - Use smaller partition scheme

4. **Fall back to USB**:
   ```bash
   # Just use USB if OTA won't work
   pio run --target upload
   ```

### Problem: Preferences Not Saving

**Symptoms**: Settings reset after reboot

**Cause**: Preferences API not working or flash corruption

**Solutions**:

1. **Check namespace**:
   ```cpp
   // Must call begin() before use:
   prefs.begin(PREF_NAMESPACE, false);
   ```

2. **Verify writes**:
   ```cpp
   prefs.putString("key", "value");
   bool saved = prefs.getBool("key", "");
   Serial.printf("Saved: %s\n", saved.c_str());
   ```

3. **Clear preferences**:
   ```cpp
   prefs.clear();  // Erase all keys
   prefs.end();
   ESP.restart();
   ```

4. **Flash wear**:
   - Flash has limited write cycles (~100,000)
   - Don't save on every loop iteration!

---

## Section 6: Battery Issues

### Problem: Battery Drains Quickly

**Expected**: 10-14 days per charge  
**Getting**: < 5 days

**Causes**:

1. **LEDs too bright**:
   - Solution: Reduce brightness to 64

2. **Deep sleep not working**:
   ```bash
   # Serial monitor should show:
   [INFO] Entering deep sleep...
   # When clocked out
   ```

3. **WiFi staying active**:
   - Check if WiFi disconnects properly

4. **Old battery**:
   - After 300-500 cycles, capacity degrades
   - Solution: Replace battery

**Measuring current draw**:
```bash
# Use USB power meter:
# Idle (clocked out, sleeping): < 0.01A (10mA)
# Active (WiFi, LEDs): 0.10-0.15A (100-150mA)
# If higher → Find power drain
```

### Problem: Battery Won't Charge

**Symptoms**: Plug in USB, no TP4056 LED

**Solutions**:

1. **Check USB cable**:
   - Try different cable (some are charge-only)
   - Check port (USB 2.0/3.0 should both work)

2. **Check TP4056 connections**:
   - USB VCC/GND connected?
   - BAT+/BAT- connected to battery?

3. **Battery over-discharged**:
   - If < 2.0V, protection circuit may have triggered
   - Try "wake-up" charge with adjustable power supply (3.7V, 100mA)

4. **Replace TP4056**:
   - Module may be damaged
   - Cost: $1, easy to replace

### Problem: Battery Swelling

**⚠️ DANGER!** Swollen LiPo batteries can catch fire!

**What to do**:

1. **Immediately disconnect battery**
2. **Do NOT puncture**
3. **Place in fireproof container** (metal ammo box)
4. **Dispose at electronics recycling center**
5. **Buy new battery**

**Prevention**:
- Don't over-charge (4.2V max)
- Don't over-discharge (3.0V min)
- Don't expose to heat
- Use TP4056 protection circuit (always!)

---

## Section 7: General Troubleshooting

### Problem: Everything Worked Yesterday, Not Today

**Check**:

1. **Did WiFi password change?**
   - Reset device config and re-enter

2. **Did API token expire?**
   - Many APIs have token expiration
   - Generate new token and update

3. **Is API server down?**
   - Test with curl from computer
   - Check server logs

4. **Did battery die?**
   - Plug in USB, wait 10 minutes, try again

5. **Firmware corrupted?**
   - Re-flash firmware via USB

### Getting More Help

**Gather this info before asking for help**:

1. **Firmware version**:
   ```bash
   # Serial monitor first line:
   Wall Clock In Machine v1.0.0
   ```

2. **Error logs**:
   ```bash
   # Copy full serial output showing error
   ```

3. **What you tried**:
   - List troubleshooting steps already attempted

4. **Hardware setup**:
   - Photo of device internals (if applicable)
   - Wiring diagram

**Where to ask**:
- GitHub Issues: [github.com/yourusername/wallClockInMachine/issues](https://github.com/yourusername/wallClockInMachine/issues)
- Reddit: r/esp32, r/arduino
- Arduino Forum
- Discord: ESP32 community servers

---

## Preventive Maintenance

**To avoid issues**:

✅ Charge battery before fully depleted  
✅ Keep firmware updated  
✅ Monitor serial logs periodically  
✅ Test API separately from device  
✅ Use quality components (don't cheap out on battery!)  
✅ Keep backups of configuration  
✅ Protect device from water, heat, drops  

---

## Emergency Recovery

### Complete Factory Reset

**When all else fails**:

```bash
# 1. Erase flash completely
esptool.py --port /dev/cu.usbserial-110 erase_flash

# 2. Re-upload bootloader (if needed)
esptool.py --port /dev/cu.usbserial-110 write_flash 0x1000 bootloader.bin

# 3. Upload firmware
pio run --target upload

# 4. Reconfigure from scratch
# Hold button for 5 seconds → Config mode
```

### Hardware Reset

1. Disconnect battery
2. Disconnect USB
3. Wait 30 seconds (capacitors fully discharge)
4. Press and hold RESET button
5. Reconnect power while holding RESET
6. Release after 5 seconds

### Reverting to Known-Good Firmware

```bash
# Download previous release from GitHub
# Flash specific version:
pio run --target upload --environment esp32-c3-devkitm-1@v0.9.0
```

---

**Still stuck?** Open an issue with full details! We're here to help. 🚀
