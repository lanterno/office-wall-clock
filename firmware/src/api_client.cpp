/**
 * API Client - Implementation
 */

#include "api_client.h"

ApiClient::ApiClient() {
  secure_client = new WiFiClientSecure();
  secure_client->setInsecure();  // Skip certificate validation (use with caution!)
}

ApiClient::~ApiClient() {
  delete secure_client;
}

void ApiClient::begin(const char* endpoint, const char* token) {
  api_endpoint = String(endpoint);
  api_token = String(token);
  LOG_INFO("API client configured for: %s", endpoint);
}

bool ApiClient::isConfigured() {
  return api_endpoint.length() > 0;
}

ApiResponse ApiClient::sendRequest(const char* method, const char* path, const char* payload) {
  ApiResponse response;
  response.success = false;
  response.http_code = 0;
  
  if (!isConfigured()) {
    LOG_ERROR("API client not configured");
    response.error_message = "API not configured";
    return response;
  }
  
  String url = api_endpoint + String(path);
  LOG_INFO("API %s %s", method, url.c_str());
  
  // Retry logic
  for (int attempt = 0; attempt < API_RETRY_COUNT; attempt++) {
    if (attempt > 0) {
      LOG_WARN("Retry attempt %d/%d", attempt + 1, API_RETRY_COUNT);
      delay(1000 * attempt);  // Exponential backoff
    }
    
    http.begin(*secure_client, url);
    http.setTimeout(API_TIMEOUT_MS);
    http.addHeader("Content-Type", "application/json");
    
    if (api_token.length() > 0) {
      http.addHeader("Authorization", "Bearer " + api_token);
    }
    
    int http_code = 0;
    if (strcmp(method, "GET") == 0) {
      http_code = http.GET();
    } else if (strcmp(method, "POST") == 0) {
      http_code = http.POST(payload ? payload : "{}");
    }
    
    response.http_code = http_code;
    
    if (http_code > 0) {
      String response_body = http.getString();
      LOG_DEBUG("HTTP %d: %s", http_code, response_body.c_str());
      
      if (http_code >= 200 && http_code < 300) {
        // Parse JSON response
        StaticJsonDocument<512> doc;
        DeserializationError error = deserializeJson(doc, response_body);
        
        if (!error) {
          response.success = true;
          
          if (doc.containsKey("beat_id")) {
            response.beat_id = doc["beat_id"].as<String>();
          }
          
          if (doc.containsKey("started_at") || doc.containsKey("created_at")) {
            // Parse timestamp if needed
            response.timestamp = millis();  // Simplified for now
          }
          
          http.end();
          return response;
        } else {
          LOG_ERROR("JSON parsing failed: %s", error.c_str());
          response.error_message = "Invalid JSON response";
        }
      } else {
        LOG_ERROR("HTTP error: %d", http_code);
        response.error_message = "HTTP " + String(http_code);
      }
    } else {
      LOG_ERROR("HTTP request failed: %s", http.errorToString(http_code).c_str());
      response.error_message = "Connection failed";
    }
    
    http.end();
  }
  
  return response;
}

ApiResponse ApiClient::clockIn(const char* project_id) {
  StaticJsonDocument<256> doc;
  doc["project_id"] = project_id;
  
  String payload;
  serializeJson(doc, payload);
  
  LOG_INFO("Clocking in to project: %s", project_id);
  return sendRequest("POST", "/api/timer/start", payload.c_str());
}

ApiResponse ApiClient::clockOut(const char* beat_id) {
  StaticJsonDocument<256> doc;
  doc["beat_id"] = beat_id;
  
  String payload;
  serializeJson(doc, payload);
  
  LOG_INFO("Clocking out from beat: %s", beat_id);
  return sendRequest("POST", "/api/timer/stop", payload.c_str());
}

ApiResponse ApiClient::getCurrentStatus() {
  LOG_INFO("Fetching current timer status");
  return sendRequest("GET", "/api/timer/current", nullptr);
}
