# API Integration

The Wall Clock In Machine is designed to work with **your existing timer API**. This guide explains how to configure the device to communicate with your backend service.

## API Requirements

Your timer API must provide HTTP/HTTPS endpoints for:

1. **Starting a timer** (clock in)
2. **Stopping a timer** (clock out)
3. **Getting current status** (optional, for recovery)

!!! info "External Dependency"
    The Wall Clock In Machine does not include a backend API. You must have your own timer tracking service running. The device acts as a physical interface to your existing API.

## Default API Format (current Rust firmware)

The minimal Rust firmware is configured for a **single toggle endpoint**:

```http
POST /api/timer/toggle
Host: 192.168.1.100:8000
Content-Length: 0
Connection: close
```

- No JSON body is sent by default.
- Any `2xx` response is treated as a success.
- The endpoint is controlled by `NETWORK_CONFIG.api_host`, `api_port`, and
  `api_path` in `firmware/src/config.rs`.

You can still build a more traditional API with separate start/stop endpoints – see
“Adapting to Your API” below.

## Configuration (Rust firmware)

All network and API configuration currently lives in code:

- File: `firmware/src/config.rs`
- Constant: `NETWORK_CONFIG`

See the [Configuration](configuration.md) page for the exact Rust snippet and
step-by-step instructions.

!!! warning "HTTPS Recommended"
    For security, use HTTPS for your API endpoint. The device supports both HTTP and HTTPS, but HTTP sends your token in plain text over WiFi.

## Adapting to Your API

If your API uses different endpoint paths or request formats, you can modify the firmware.

### Changing Endpoint Path

Edit `NETWORK_CONFIG` in `firmware/src/config.rs`:

```rust
pub const NETWORK_CONFIG: NetworkConfig = NetworkConfig {
    wifi_ssid: "YOUR_WIFI_SSID",
    wifi_password: "YOUR_WIFI_PASSWORD",
    api_host: "your-api-domain.com",
    api_port: 443,
    api_path: "/your/custom/path",
};
```

### Sending a JSON body (advanced)

The minimal firmware sends an empty body, but you can change `handle_clock_toggle`
in `firmware/src/tasks/wifi.rs` to send JSON instead:

```rust
#[derive(serde::Serialize)]
struct TogglePayload<'a> {
    action: &'a str,
}

let payload = TogglePayload { action: "toggle" };
let body = serde_json_core::to_string::<_, heapless::String<128>>(&payload)
    .map_err(|_| "json")?;

write!(
    &mut request,
    "POST {} HTTP/1.1\r\nHost: {}\r\nContent-Type: application/json\r\nContent-Length: {}\r\nConnection: close\r\n\r\n{}",
    cfg.api_path,
    cfg.api_host,
    body.len(),
    body,
)?;
```

You can extend the payload to match your API (e.g., project IDs, auth tokens).

## Testing Your API

Before using the device, test your API manually:

### Test Clock In

```bash
curl -X POST https://your-api.com/api/timer/start \
  -H "Content-Type: application/json" \
  -H "Authorization: Bearer YOUR_TOKEN" \
  -d '{"project_id": "office-time"}'
```

**Expected**: 200 OK with `beat_id` in response

### Test Clock Out

```bash
curl -X POST https://your-api.com/api/timer/stop \
  -H "Content-Type: application/json" \
  -H "Authorization: Bearer YOUR_TOKEN" \
  -d '{"beat_id": "12345"}'
```

**Expected**: 200 OK confirming stop

### Test from Device Network

Test from same network as device:

```bash
# SSH into a device on same network or test from laptop on WiFi
curl -v https://your-api.com/api/timer/start \
  -H "Content-Type: application/json" \
  -H "Authorization: Bearer YOUR_TOKEN" \
  -d '{"project_id": "office-time"}'
```

**Check**:
- ✅ DNS resolves correctly
- ✅ SSL certificate valid
- ✅ Firewall allows connection
- ✅ API responds with 200 OK

## Authentication Methods

### Bearer Token (Recommended)

```cpp
// In api_client.cpp:
http.addHeader("Authorization", "Bearer " + api_token);
```

Set token in device configuration portal.

### API Key

```cpp
// In api_client.cpp:
http.addHeader("X-API-Key", api_token);
```

### Basic Auth

```cpp
// In api_client.cpp:
String auth = base64::encode(api_token + ":" + api_password);
http.addHeader("Authorization", "Basic " + auth);
```

### OAuth2

For OAuth2, you'll need to implement token refresh logic. This is advanced - see the firmware source code in the repository.

## Network Requirements

### Firewall Configuration

Ensure your API is accessible:

- ✅ Allow incoming HTTPS (port 443) from your network
- ✅ If using HTTP, allow port 80
- ✅ If API is on local network, ensure ESP32 can reach it

### DNS

If using a domain name:

- ✅ Ensure DNS resolves from your WiFi network
- ✅ Test: `nslookup your-api-domain.com`

### SSL/TLS

The device uses `WiFiClientSecure` with insecure mode by default:

```cpp
secure_client->setInsecure();  // Skips certificate validation
```

For production, add certificate validation:

```cpp
// In api_client.cpp:
const char* rootCA = R"EOF(
-----BEGIN CERTIFICATE-----
YOUR_CERTIFICATE_HERE
-----END CERTIFICATE-----
)EOF";

secure_client->setCACert(rootCA);
```

## Error Handling

The device handles common errors:

### Network Errors

- **Connection Failed**: Retries 3 times with exponential backoff
- **Timeout**: 10-second timeout per request
- **DNS Failure**: Shows yellow LED, retries on next button press

### HTTP Errors

| Code | Meaning | Device Behavior |
|------|---------|----------------|
| **200-299** | Success | Green LED, normal operation |
| **401** | Unauthorized | Yellow LED, check token |
| **403** | Forbidden | Yellow LED, check permissions |
| **404** | Not Found | Yellow LED, check endpoint path |
| **429** | Rate Limited | Yellow LED, waits 1 minute |
| **500** | Server Error | Yellow LED, retries |
| **502/503** | Unavailable | Yellow LED, retries |

### Offline Mode

If API is unreachable:

1. Device stores state locally (beat_id, timestamp)
2. Shows yellow LED to indicate offline
3. Retries periodically when button pressed
4. Syncs when connection restored

## API Integration Examples

### Minimal Example Backend (FastAPI)

The easiest way to try the device end‑to‑end is to run a tiny local backend that
implements the `/api/timer/toggle` endpoint the firmware expects:

```python
# backend.py
from fastapi import FastAPI
from pydantic import BaseModel
from datetime import datetime

app = FastAPI()

class State(BaseModel):
    is_running: bool = False
    last_toggle: datetime | None = None

state = State()

@app.post("/api/timer/toggle")
def toggle():
    state.is_running = not state.is_running
    state.last_toggle = datetime.utcnow()
    return state
```

Run it locally:

```bash
pip install fastapi uvicorn
uvicorn backend:app --host 0.0.0.0 --port 8000
```

Then set in `NETWORK_CONFIG`:

```rust
api_host: "192.168.1.100", // your dev machine IP on WiFi
api_port: 8000,
api_path: "/api/timer/toggle",
```

Pressing the button will now flip `is_running` on your backend.

## Monitoring API Calls

### Serial Monitor

Connect device via USB to see API calls:

```bash
espflash monitor --speed 115200
```

Output:
```
[INFO] Button pressed: Clock In
[API] POST /api/timer/start
[API] Response: 200 OK
[INFO] Clocked in successfully! Beat ID: 12345
```

### API Logs

Check your API server logs to verify:

- Requests are reaching the server
- Authentication is working
- Correct response format
- Response time < 10 seconds

## Security Best Practices

!!! warning "Security Considerations"
    1. **Use HTTPS** - Encrypts traffic including tokens
    2. **Rotate Tokens** - Change API tokens periodically
    3. **Limit Scope** - Use tokens with minimal permissions
    4. **Network Security** - Use WPA2/WPA3 for WiFi
    5. **Device Physical Security** - Device stores token in flash memory

### Token Storage

Tokens are stored in ESP32 non-volatile storage:

- Encrypted by ESP32 hardware (flash encryption)
- Persists across reboots
- Can be wiped with factory reset

## Troubleshooting

### "Connection Failed" Error

**Possible Causes**:
- API server is down
- DNS not resolving
- Firewall blocking ESP32
- Network connectivity issue

**Solutions**:
1. Test API with curl from same network
2. Check API server status
3. Verify firewall rules
4. Check WiFi connection

### "HTTP 401 Unauthorized"

**Cause**: Invalid or missing API token

**Solution**:
1. Verify token is correct
2. Check token hasn't expired
3. Ensure token has required permissions
4. Update token in device configuration

### "HTTP 404 Not Found"

**Cause**: Wrong API endpoint path

**Solution**:
1. Verify API endpoint URL in configuration
2. Check API documentation for correct paths
3. Modify firmware if paths are different

### "Timeout" Error

**Cause**: API response time > 10 seconds

**Solutions**:
1. Optimize API performance
2. Increase timeout in `firmware/src/config.h`:
   ```cpp
   #define API_TIMEOUT_MS  20000  // 20 seconds
   ```
3. Check for slow database queries

## Next Steps

- **Configure Device**: [Configuration Guide](configuration.md)
- **Test Setup**: [Testing Guide](../assembly/final-testing.md)
- **Daily Use**: [Usage Guide](../usage/daily-operation.md)

---

**Need Help?** Check the [Configuration Guide](configuration.md) or open an issue on GitHub.
