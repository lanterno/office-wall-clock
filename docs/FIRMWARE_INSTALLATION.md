# Firmware Installation Guide

**Time Required**: 30-45 minutes (first time), 5 minutes (updates)  
**Skill Level**: Beginner  
**Prerequisites**: Computer with USB port, internet connection

## Overview

This guide will help you install the firmware on your Wall Clock In Machine. You'll learn how to:

1. Set up the development environment
2. Download the firmware
3. Configure for your setup
4. Upload to the device
5. Verify it works
6. Update firmware in the future

---

## Method 1: PlatformIO (Recommended)

**Best for**: Developers, people comfortable with command line

### Step 1: Install Prerequisites

**Install Python** (if not already installed):
```bash
# macOS (using Homebrew)
brew install python3

# Verify installation
python3 --version
```

**Install PlatformIO Core**:
```bash
# Install via pip
pip3 install platformio

# Verify installation
pio --version
```

### Step 2: Download Firmware

**Option A: Clone Git Repository**
```bash
cd ~/projects/
git clone https://github.com/yourusername/wallClockInMachine.git
cd wallClockInMachine/firmware/
```

**Option B: Download ZIP**
1. Go to GitHub repository
2. Click "Code" → "Download ZIP"
3. Extract to your projects folder
4. Navigate to `firmware/` directory

### Step 3: Install Dependencies

```bash
cd firmware/

# PlatformIO will automatically install all libraries
pio lib install

# This installs:
# - FastLED (LED control)
# - WiFiManager (WiFi setup)
# - ArduinoJson (JSON parsing)
```

### Step 4: Build Firmware

```bash
# Build firmware (compiles but doesn't upload)
pio run

# Expected output:
# ...
# Building in release mode
# ...
# ============ [SUCCESS] ============
```

**Troubleshooting Build Errors**:
- `platformio: command not found` → Add to PATH or use full path
- `No module named 'platformio'` → Reinstall PlatformIO
- `Library not found` → Run `pio lib install` again

### Step 5: Connect Device

1. Connect ESP32-C3 to computer via USB-C cable
2. Board should appear as serial device

**Find your device port**:
```bash
# macOS/Linux
pio device list

# Look for output like:
# /dev/cu.usbserial-110  ESP32-C3

# Your port might be:
# macOS: /dev/cu.usbserial-* or /dev/cu.wchusbserial*
# Linux: /dev/ttyUSB0 or /dev/ttyACM0
```

### Step 6: Upload Firmware

```bash
# Upload firmware to device
pio run --target upload

# Or specify port explicitly:
pio run --target upload --upload-port /dev/cu.usbserial-110

# Expected output:
# ...
# Writing at 0x00010000... (100 %)
# Wrote 123456 bytes (67890 compressed)
# Hash of data verified.
# Leaving... Hard resetting via RTS pin...
# ============ [SUCCESS] ============
```

**Common Upload Issues**:
- `Failed to connect to ESP32` → Press and hold BOOT button while uploading
- `Permission denied` → Add user to dialout group (Linux) or use sudo
- `Could not open port` → Close any serial monitors first

### Step 7: Monitor Serial Output

```bash
# Open serial monitor
pio device monitor

# Or with specific baud rate:
pio device monitor --baud 115200

# You should see:
# =================================
# Wall Clock In Machine v1.0.0
# =================================
# [INFO] Connecting to WiFi...
```

**To exit monitor**: Press `Ctrl+C`

---

## Method 2: Arduino IDE (Easier for Beginners)

**Best for**: First-time users, visual preference

### Step 1: Install Arduino IDE

1. Download from [arduino.cc/en/software](https://www.arduino.cc/en/software)
2. Install for your operating system
3. Launch Arduino IDE 2.0+

### Step 2: Install ESP32 Board Support

**In Arduino IDE**:
1. Go to `File` → `Preferences`
2. Add to "Additional Board Manager URLs":
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
3. Click `OK`
4. Go to `Tools` → `Board` → `Boards Manager`
5. Search for "esp32"
6. Install "esp32 by Espressif Systems" (version 2.0.14 or later)
7. Wait for installation to complete

### Step 3: Install Required Libraries

**In Arduino IDE**:
1. Go to `Sketch` → `Include Library` → `Manage Libraries`
2. Search and install each:
   - **FastLED** by Daniel Garcia
   - **WiFiManager** by tzapu
   - **ArduinoJson** by Benoit Blanchon

### Step 4: Open Firmware

1. Download firmware from GitHub (see Method 1, Step 2)
2. In Arduino IDE: `File` → `Open`
3. Navigate to `firmware/src/main.cpp`
4. Click `Open`

### Step 5: Configure Board Settings

**In Arduino IDE**:
1. Go to `Tools` → `Board` → `ESP32 Arduino` → `ESP32C3 Dev Module`
2. Set these options:
   - **CPU Frequency**: 160MHz
   - **Flash Frequency**: 80MHz
   - **Flash Mode**: QIO
   - **Flash Size**: 4MB
   - **Partition Scheme**: Default 4MB with spiffs
   - **Upload Speed**: 921600
   - **USB CDC On Boot**: Enabled
   - **USB Mode**: Hardware CDC and JTAG
   - **Port**: Select your ESP32-C3 device

### Step 6: Upload

1. Connect ESP32-C3 via USB-C
2. Click the **Upload** button (→ arrow icon)
3. Wait for compilation and upload
4. Watch for "Done uploading" message

### Step 7: Open Serial Monitor

1. Click `Tools` → `Serial Monitor`
2. Set baud rate to `115200`
3. You should see device boot messages

---

## Method 3: Pre-Compiled Binary (Quickest)

**Best for**: Non-developers, quick testing

### Step 1: Download ESPTool

```bash
# Install esptool
pip3 install esptool

# Verify
esptool.py version
```

### Step 2: Download Pre-Compiled Firmware

1. Go to [GitHub Releases](https://github.com/yourusername/wallClockInMachine/releases)
2. Download latest `firmware.bin`
3. Save to your Downloads folder

### Step 3: Flash Firmware

```bash
# Navigate to downloads
cd ~/Downloads/

# Find your device port
esptool.py --port /dev/cu.usbserial-110 chip_id

# Flash firmware
esptool.py --port /dev/cu.usbserial-110 write_flash 0x10000 firmware.bin

# Expected output:
# ...
# Hash of data verified.
# 
# Leaving...
# Hard resetting via RTS pin...
```

**Parameters Explanation**:
- `--port`: Your device's serial port
- `write_flash`: Command to write firmware
- `0x10000`: Memory address (don't change)
- `firmware.bin`: Your firmware file

---

## Configuration After Installation

### First Boot

When device powers on for first time:

1. **Blue LED** pulses (trying to connect to WiFi)
2. After 30 seconds, creates WiFi hotspot: `WallClockIn-Setup`
3. Connect to this hotspot with phone or computer
4. Browser opens automatically (or go to http://192.168.4.1)
5. Enter your WiFi credentials and API endpoint
6. Click **Save**
7. Device reboots and connects to your WiFi

### Detailed Configuration

See [Configuration Guide](CONFIGURATION.md) for complete setup instructions.

---

## Verifying Installation

### Check Serial Output

Connect to serial monitor and look for:

```
=================================
Wall Clock In Machine v1.0.0
=================================
[INFO] Button handler initialized on pin 9
[INFO] LED controller initialized with 8 LEDs
[INFO] Connecting to WiFi...
[INFO] WiFi connected!
[INFO] IP address: 192.168.1.42
[INFO] API client configured for: https://api.example.com
[INFO] System ready!
[INFO] Battery: 87% (3.92V)
```

### Visual Checks

- ✅ Status LED lights up (color depends on state)
- ✅ Pressing button changes LED color
- ✅ Energy meter LEDs light up when clocked in
- ✅ Device responds within 1 second

### Test API Connection

1. Press toggle button → Clock In
2. Watch serial monitor for:
   ```
   [INFO] Button pressed: Clock In
   [API] POST /api/timer/start
   [API] Response: 200 OK
   [INFO] Now working, energy meter started
   ```
3. Status LED should turn **green**
4. Energy meter should show 8 hours remaining

---

## Updating Firmware

### Over-The-Air (OTA) Updates

**Once device is on WiFi**, you can update wirelessly!

```bash
cd firmware/

# Upload via OTA (must be on same network)
pio run --target upload --upload-port wall-clock-in.local

# Or use IP address directly:
pio run --target upload --upload-port 192.168.1.42
```

**Advantages**:
- No USB cable needed
- Update device while it's mounted on desk
- Faster than USB

**Requirements**:
- Device must be powered on
- Connected to same WiFi network
- OTA enabled in firmware (default)

### USB Updates

Same as initial installation:

```bash
# Connect via USB-C
pio run --target upload
```

### Automatic Update Check

**Future Feature**: Device will check for updates daily and prompt you.

---

## Troubleshooting

### "Could not open port" Error

**Cause**: Port is already in use or permission issue

**Solutions**:
```bash
# macOS: Reset USB device
sudo killall -STOP -c usb

# Linux: Add user to dialout group
sudo usermod -a -G dialout $USER
# Then log out and back in

# Or use sudo (not recommended)
sudo pio run --target upload
```

### "Failed to connect to ESP32" Error

**Cause**: Device not in bootloader mode

**Solutions**:
1. Hold **BOOT** button on ESP32
2. Press **RESET** button briefly
3. Release **BOOT** button
4. Try upload again

Or:

1. Disconnect USB
2. Hold **BOOT** button
3. Connect USB while holding
4. Release **BOOT** after 2 seconds
5. Try upload

### "Brownout detector was triggered" Error

**Cause**: Insufficient power from USB port

**Solutions**:
- Use different USB port (avoid hubs)
- Use powered USB hub
- Try different USB cable (some are charge-only)
- Connect directly to computer, not through hub

### Upload Works But Device Doesn't Boot

**Possible Causes**:
1. Wrong board selected in Arduino IDE
2. Incorrect partition scheme
3. Corrupted firmware

**Solutions**:
1. Erase flash completely:
   ```bash
   esptool.py --port /dev/cu.usbserial-110 erase_flash
   ```
2. Re-upload firmware
3. Check serial monitor for errors

### Libraries Not Found

**Arduino IDE**:
1. `Sketch` → `Include Library` → `Manage Libraries`
2. Reinstall each library
3. Restart Arduino IDE

**PlatformIO**:
```bash
# Clean and reinstall
pio lib uninstall --all
pio lib install
```

---

## Development Tips

### Enable Debug Logging

In `src/config.h`, change:
```cpp
#define LOG_LEVEL LOG_LEVEL_DEBUG
```

This shows detailed information:
```
[DEBUG] Button pressed
[DEBUG] LED brightness set to 128
[DEBUG] Energy meter: 6/8 hours, 5 LEDs lit
```

### Test Mode

Hold button during boot for 5 seconds to enter test modes:
- LED test: All LEDs cycle through colors
- WiFi test: Show IP address
- API test: Send test request
- Battery test: Show voltage and percentage

### Debugging Tools

**PlatformIO Debugger** (advanced):
```bash
# Launch debugger
pio debug

# Set breakpoint at main.cpp line 50
break main.cpp:50

# Continue execution
continue
```

---

## Next Steps

✅ Firmware installed successfully!

**Continue to**:
1. [Configuration Guide](CONFIGURATION.md) - Set up WiFi and API
2. [Usage Guide](USAGE_GUIDE.md) - Daily operation
3. [Troubleshooting](TROUBLESHOOTING.md) - Common issues

---

**Questions?** Check the [FAQ](FAQ.md) or open an issue on GitHub!
