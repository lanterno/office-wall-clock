# Configuration Guide

**Time Required**: 15 minutes  
**Prerequisite**: Firmware installed (see [Firmware Installation](FIRMWARE_INSTALLATION.md))

## Overview

This guide covers:
1. WiFi setup
2. API endpoint configuration  
3. Customizing settings
4. Testing configuration
5. Troubleshooting

---

## First-Time Setup

### Step 1: Power On Device

1. Ensure battery is charged (USB-C for 2 hours)
2. Turn on device (if toggle switch used as power switch)
3. **Blue LED** should start pulsing

### Step 2: Connect to Setup WiFi

The device will try to connect to saved WiFi. If none configured:

**On your phone or computer:**
1. Open WiFi settings
2. Look for network: **WallClockIn-Setup**
3. Connect (no password needed)
4. Wait 3-5 seconds

**A configuration page should open automatically**
- If not, open browser and go to: `http://192.168.4.1`

### Step 3: Configure WiFi

**On the configuration page:**

1. Click "**Configure WiFi**"
2. Select your WiFi network from the list
3. Enter WiFi password
4. Scroll down to custom parameters:

**API Endpoint**:
```
https://your-api-domain.com
```
(Don't include `/api/timer/start` - just the base URL)

**API Token** (optional):
```
your_bearer_token_here
```
If your API requires authentication, enter your token.

5. Click "**Save**"

### Step 4: Wait for Connection

- Device will save settings and reboot
- **Blue LED** pulses while connecting
- After 10-30 seconds:
  - ✅ **Red LED** = Connected successfully (clocked out)
  - ❌ **Yellow LED** = Connection failed

---

## Verifying Configuration

### Check Serial Monitor

If you have device connected via USB:

```bash
# Open serial monitor
pio device monitor --baud 115200

# You should see:
[INFO] WiFi connected!
[INFO] IP address: 192.168.1.42
[INFO] API client configured for: https://your-api-domain.com
[INFO] System ready!
```

### Test Button

1. Press toggle button
2. Watch serial output:
   ```
   [INFO] Button pressed: Clock In
   [API] POST /api/timer/start
   [API] Response: 200 OK
   [INFO] Clocked in successfully! Beat ID: 12345
   ```
3. Status LED should turn **green**
4. Energy meter LEDs should light up (7 LEDs for 8 hours)

### Check Your API

On your API backend, verify that the timer was started:

```bash
# Example: Check current status
curl https://your-api-domain.com/api/timer/current \
  -H "Authorization: Bearer your_token"

# Expected response:
{
  "is_running": true,
  "beat_id": "12345",
  "started_at": "2025-10-29T08:00:00Z",
  "elapsed": 120
}
```

---

## API Endpoint Configuration

### Format Requirements

**Correct formats**:
```
https://api.example.com
http://192.168.1.100:8000
https://mydomain.com/beats
```

**Incorrect formats** (don't include endpoints):
```
❌ https://api.example.com/api/timer/start  (too specific)
❌ api.example.com  (missing protocol)
❌ https://api.example.com/  (trailing slash ok, but not needed)
```

### API Endpoints Used

The device will make requests to these paths:

**Clock In**:
```
POST {your_endpoint}/api/timer/start
Content-Type: application/json
Authorization: Bearer {your_token}

{
  "project_id": "office-time"
}
```

**Clock Out**:
```
POST {your_endpoint}/api/timer/stop
Content-Type: application/json
Authorization: Bearer {your_token}

{
  "beat_id": "12345"
}
```

**Get Status** (for recovery):
```
GET {your_endpoint}/api/timer/current
Authorization: Bearer {your_token}
```

### Adapting to Your API

If your API has different endpoints, you'll need to modify the firmware:

**In `firmware/src/api_client.cpp`**, change the paths:

```cpp
// Change from:
ApiResponse ApiClient::clockIn(const char* project_id) {
  return sendRequest("POST", "/api/timer/start", payload.c_str());
}

// To your API's path:
ApiResponse ApiClient::clockIn(const char* project_id) {
  return sendRequest("POST", "/your/custom/path", payload.c_str());
}
```

Then re-upload firmware.

---

## Advanced Settings

### Changing Work Hours

Default is 8 hours. To change:

**Option 1: Via Preferences (requires code modification)**

In `firmware/src/config.h`:
```cpp
#define DEFAULT_WORK_HOURS  7  // Change to your desired hours
```

**Option 2: Via Serial Commands** (future feature)

```
> set work_hours 7
Work hours set to 7
```

### Adjusting LED Brightness

**Via code** (in `firmware/src/config.h`):
```cpp
#define LED_BRIGHTNESS  64   // 0-255, lower = dimmer
```

**Via configuration portal** (future feature)

### Changing Project ID

The device sends `"project_id": "office-time"` by default.

To change:

**In `firmware/src/config.h`**:
```cpp
#define PROJECT_ID  "your-project-name"
```

### Enable/Disable Deep Sleep

Deep sleep saves battery when clocked out.

**In `firmware/src/config.h`**:
```cpp
// To disable sleep (always stay awake):
#define ENABLE_DEEP_SLEEP  false
```

---

## Reconfiguring Device

### Method 1: Long Press Reset

1. Hold toggle button for **5 seconds**
2. Status LED turns **white** (config mode)
3. Device creates WiFi hotspot again
4. Follow "First-Time Setup" steps above

### Method 2: Factory Reset

**Via Serial Monitor**:
```bash
# Connect via USB
pio device monitor

# Type:
reset

# Device will erase all settings and reboot
```

**Via Button During Boot**:
1. Disconnect power
2. Hold toggle button
3. Connect power while holding
4. Wait for white LED
5. Release button

---

## Updating Configuration Without Reset

### Via Web Interface (future feature)

When device is connected to WiFi:

1. Open browser
2. Go to `http://wall-clock-in.local` (or device IP)
3. Log in (default password: `admin`)
4. Update settings
5. Click Save

### Via Serial Commands

```bash
# Connect serial monitor
pio device monitor

# Update API endpoint
> set api_endpoint https://new-api.com
API endpoint updated

# Update API token
> set api_token new_token_here
API token updated

# Save changes
> save
Configuration saved

# Reboot to apply
> reboot
```

---

## WiFi Troubleshooting

### Can't See "WallClockIn-Setup" Network

**Possible causes**:
- Device already connected to your WiFi
- Waiting period hasn't elapsed (wait 30 seconds)
- Device in error state

**Solutions**:
1. Hold button for 5 seconds (force config mode)
2. Power cycle device
3. Check if device already connected (check router)

### Won't Connect to Home WiFi

**Common issues**:

**5GHz Network**: ESP32 only supports 2.4GHz
- Solution: Use 2.4GHz network or set up dual-band

**Special Characters in Password**: Some characters cause issues
- Solution: Change WiFi password to alphanumeric

**Hidden Network**: Must enter SSID manually
- Solution: Type SSID in custom field

**MAC Filtering**: Router blocks unknown devices
- Solution: Add device MAC to whitelist

**Weak Signal**: Too far from router
- Solution: Move closer during setup, or use WiFi extender

### Connection Drops Frequently

**Causes**:
- Weak WiFi signal
- Router sleeps idle connections
- Power saving too aggressive

**Solutions**:
1. Move device closer to router
2. Use WiFi extender
3. Disable WiFi sleep on router
4. In firmware, disable power saving:
   ```cpp
   WiFi.setSleep(false);
   ```

---

## API Troubleshooting

### "API Error" - Yellow LED

**Check serial monitor** for specific error:

**Error: "Connection failed"**
- Device can't reach API server
- Check:
  - API endpoint URL correct?
  - Server online?
  - Firewall blocking ESP32?
  - HTTPS certificate valid?

**Error: "HTTP 401 Unauthorized"**
- API token incorrect or missing
- Update token in configuration

**Error: "HTTP 404 Not Found"**
- API endpoint path wrong
- Verify paths in `api_client.cpp`

**Error: "HTTP 500 Internal Server Error"**
- API backend has an issue
- Check API logs

**Error: "Timeout"**
- API too slow to respond (>10 seconds)
- Optimize API or increase timeout

### Testing API Manually

Before blaming the device, test your API:

```bash
# Test clock in
curl -X POST https://your-api.com/api/timer/start \
  -H "Content-Type: application/json" \
  -H "Authorization: Bearer your_token" \
  -d '{"project_id": "office-time"}'

# Expected: 200 OK with beat_id

# Test clock out
curl -X POST https://your-api.com/api/timer/stop \
  -H "Content-Type: application/json" \
  -H "Authorization: Bearer your_token" \
  -d '{"beat_id": "test123"}'

# Expected: 200 OK
```

If these fail, fix your API first.

---

## Security Considerations

### API Token Safety

**Don't**:
- Share your token publicly
- Commit token to Git
- Use admin tokens (use limited-scope token)

**Do**:
- Create device-specific API token
- Limit token permissions (only timer access)
- Rotate tokens periodically
- Revoke if device lost/stolen

### Network Security

**Recommendations**:
- Use HTTPS for API (not HTTP)
- Connect to secure WiFi (WPA2/WPA3)
- Keep firmware updated
- Don't expose device config portal to internet

---

## Configuration File Reference

Settings are stored in ESP32 non-volatile memory:

```cpp
// Namespace: "wallclock"
Preferences prefs;

// Stored keys:
api_endpoint     // String, max 128 chars
api_token        // String, max 64 chars
work_hours       // UInt8, default 8
led_brightness   // UInt8, default 128
beat_id          // String, current session
clock_in_time    // ULong, Unix timestamp
```

### Backup Configuration

To backup settings:

**Via Serial**:
```bash
> config dump
api_endpoint: https://api.example.com
api_token: abc123xyz
work_hours: 8
led_brightness: 128
```

Copy this output and save somewhere safe!

### Restore Configuration

**Via Serial**:
```bash
> config restore
> set api_endpoint https://api.example.com
> set api_token abc123xyz
> set work_hours 8
> set led_brightness 128
> save
```

---

## Next Steps

✅ Configuration complete!

**Continue to**:
- [Usage Guide](USAGE_GUIDE.md) - Daily operation
- [Troubleshooting](TROUBLESHOOTING.md) - Common issues
- [API Integration](API_INTEGRATION.md) - Customize API endpoints

---

**Questions?** Check [FAQ](FAQ.md) or open an issue!
