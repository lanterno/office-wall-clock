# Configuration

Configure WiFi, API endpoint, and device options.

## WiFi Setup
On first boot or after reset:
1. Device exposes AP: `WALL-CLOCK-SETUP`
2. Connect with phone or laptop
3. Open `http://192.168.4.1/`
4. Enter WiFi SSID and password

## API Settings
- API Base URL: e.g., `https://api.example.com`
- Start endpoint: `/api/beats/start`
- End endpoint: `/api/beats/end`
- Optional auth token header

## Device Options
- LED Brightness: 10-255 (default 64)
- Update Interval: 5 min
- Low Battery Threshold: 20%
- Timezone/NTP server

## Resetting Config
- Hold button for 10 seconds at boot → clears WiFi and settings
- Or expose settings page via admin long-press menu

## Environment Variables (for API docs site)
- BACKEND_API_BASE_URL
- BACKEND_API_TOKEN (optional)

---

See: [API Integration](api-integration.md), [Daily Operation](../usage/daily-operation.md)