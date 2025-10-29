# API Integration

The Wall Clock In Machine is designed to work with **your existing timer API**. This guide explains how to configure the device to communicate with your backend service.

## API Requirements

Your timer API must provide HTTP/HTTPS endpoints for:

1. **Starting a timer** (clock in)
2. **Stopping a timer** (clock out)
3. **Getting current status** (optional, for recovery)

!!! info "External Dependency"
    The Wall Clock In Machine does not include a backend API. You must have your own timer tracking service running. The device acts as a physical interface to your existing API.

## Default API Format

The firmware is pre-configured to work with the following API structure:

### Clock In Endpoint

```http
POST /api/timer/start
Content-Type: application/json
Authorization: Bearer {your_token}

{
  "project_id": "office-time"
}
```

**Expected Response** (200 OK):
```json
{
  "beat_id": "12345",
  "started_at": "2025-10-29T08:00:00Z"
}
```

### Clock Out Endpoint

```http
POST /api/timer/stop
Content-Type: application/json
Authorization: Bearer {your_token}

{
  "beat_id": "12345"
}
```

**Expected Response** (200 OK):
```json
{
  "beat_id": "12345",
  "stopped_at": "2025-10-29T17:00:00Z",
  "duration": 28800
}
```

### Get Status Endpoint (Optional)

```http
GET /api/timer/current
Authorization: Bearer {your_token}
```

**Expected Response** (200 OK):
```json
{
  "is_running": true,
  "beat_id": "12345",
  "started_at": "2025-10-29T08:00:00Z",
  "elapsed": 3600
}
```

## Configuration

### Environment Variables

Set these environment variables for configuration:

```bash
# API endpoint (base URL without paths)
export TIMER_API_ENDPOINT="https://your-api-domain.com"

# API authentication token (optional)
export TIMER_API_TOKEN="your_bearer_token_here"

# Project ID for time entries (optional, default: "office-time")
export TIMER_PROJECT_ID="office-time"
```

### Device Configuration

When you first power on the device, it will create a WiFi hotspot for configuration:

1. Connect to WiFi network: **WallClockIn-Setup**
2. Browser opens automatically (or go to http://192.168.4.1)
3. Enter configuration:
   - **WiFi SSID**: Your office/home WiFi
   - **WiFi Password**: Your WiFi password
   - **API Endpoint**: `https://your-api-domain.com`
   - **API Token**: Your authentication token (optional)
4. Click **Save**

The device will reboot and connect to your WiFi.

!!! warning "HTTPS Recommended"
    For security, use HTTPS for your API endpoint. The device supports both HTTP and HTTPS, but HTTP sends your token in plain text over WiFi.

## Adapting to Your API

If your API uses different endpoint paths or request formats, you can modify the firmware.

### Changing Endpoint Paths

Edit `firmware/src/api_client.cpp`:

```cpp
ApiResponse ApiClient::clockIn(const char* project_id) {
  // Change the path here:
  return sendRequest("POST", "/your/custom/start/path", payload.c_str());
}

ApiResponse ApiClient::clockOut(const char* beat_id) {
  // Change the path here:
  return sendRequest("POST", "/your/custom/stop/path", payload.c_str());
}
```

### Changing Request Format

Edit `firmware/src/api_client.cpp`:

```cpp
ApiResponse ApiClient::clockIn(const char* project_id) {
  StaticJsonDocument<256> doc;
  
  // Modify the JSON structure:
  doc["your_field_name"] = project_id;
  doc["another_field"] = "value";
  
  String payload;
  serializeJson(doc, payload);
  
  return sendRequest("POST", "/api/timer/start", payload.c_str());
}
```

### Changing Response Parsing

Edit `firmware/src/api_client.cpp` in the `sendRequest` method:

```cpp
if (doc.containsKey("your_beat_id_field")) {
  response.beat_id = doc["your_beat_id_field"].as<String>();
}
```

### Adding Custom Headers

Edit `firmware/src/api_client.cpp`:

```cpp
ApiResponse ApiClient::sendRequest(const char* method, const char* path, const char* payload) {
  // ... existing code ...
  
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", "Bearer " + api_token);
  
  // Add your custom headers:
  http.addHeader("X-Custom-Header", "value");
  http.addHeader("X-Device-ID", "wall-clock-in-machine");
  
  // ... rest of code ...
}
```

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

For OAuth2, you'll need to implement token refresh logic. This is advanced - see [Custom Features](../development/customization.md).

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

### Example 1: Toggl API

```cpp
// firmware/src/api_client.cpp

ApiResponse ApiClient::clockIn(const char* project_id) {
  StaticJsonDocument<256> doc;
  doc["time_entry"]["description"] = "Office time";
  doc["time_entry"]["created_with"] = "Wall Clock In Machine";
  
  String payload;
  serializeJson(doc, payload);
  
  return sendRequest("POST", "/api/v9/time_entries", payload.c_str());
}
```

### Example 2: Harvest API

```cpp
// firmware/src/api_client.cpp

ApiResponse ApiClient::clockIn(const char* project_id) {
  StaticJsonDocument<256> doc;
  doc["project_id"] = 12345;  // Your Harvest project ID
  doc["task_id"] = 67890;     // Your task ID
  
  String payload;
  serializeJson(doc, payload);
  
  return sendRequest("POST", "/api/v2/time_entries", payload.c_str());
}
```

### Example 3: Custom JSON Structure

```cpp
// If your API expects:
// {"action": "start", "user_id": "abc", "timestamp": 12345}

ApiResponse ApiClient::clockIn(const char* project_id) {
  StaticJsonDocument<256> doc;
  doc["action"] = "start";
  doc["user_id"] = project_id;  // Reuse project_id field
  doc["timestamp"] = millis() / 1000;
  
  String payload;
  serializeJson(doc, payload);
  
  return sendRequest("POST", "/api/timelog", payload.c_str());
}
```

## Monitoring API Calls

### Serial Monitor

Connect device via USB to see API calls:

```bash
pio device monitor --baud 115200
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
- **Troubleshoot**: [API Issues](../troubleshooting/network.md)

---

**Need Help?** Check [Troubleshooting](../troubleshooting/network.md) or open an issue on GitHub.
