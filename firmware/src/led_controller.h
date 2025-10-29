/**
 * LED Controller - Status display and energy meter
 */

#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include <Arduino.h>
#include <FastLED.h>
#include "config.h"
#include "types.h"

class LEDController {
private:
  CRGB leds[NUM_LEDS];
  uint8_t brightness;
  unsigned long last_animation_time;
  uint8_t animation_step;
  
  CRGB getColorForStatus(StatusColor status);
  void setStatusLED(StatusColor color);
  
public:
  LEDController();
  void begin();
  void setBrightness(uint8_t level);
  void setStatus(StatusColor color);
  void setEnergyMeter(uint8_t hours_remaining, uint8_t total_hours);
  void pulseStatus(StatusColor color);  // Breathing animation
  void rainbowCelebration();            // Workday complete!
  void clear();
  void update();  // Call in loop for animations
};

#endif // LED_CONTROLLER_H
