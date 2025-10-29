/**
 * API Client - HTTP communication with Timer API
 */

#ifndef API_CLIENT_H
#define API_CLIENT_H

#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include "config.h"
#include "types.h"

class ApiClient {
private:
  String api_endpoint;
  String api_token;
  HTTPClient http;
  WiFiClientSecure* secure_client;
  
  ApiResponse sendRequest(const char* method, const char* path, const char* payload);
  
public:
  ApiClient();
  ~ApiClient();
  void begin(const char* endpoint, const char* token);
  ApiResponse clockIn(const char* project_id);
  ApiResponse clockOut(const char* beat_id);
  ApiResponse getCurrentStatus();
  bool isConfigured();
};

#endif // API_CLIENT_H
