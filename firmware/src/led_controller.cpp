/**
 * LED Controller - Implementation
 */

#include "led_controller.h"

LEDController::LEDController() 
  : brightness(LED_BRIGHTNESS),
    last_animation_time(0),
    animation_step(0) {
}

void LEDController::begin() {
  FastLED.addLeds<LED_TYPE, PIN_LED_DATA, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(brightness);
  clear();
  LOG_INFO("LED controller initialized with %d LEDs", NUM_LEDS);
}

void LEDController::setBrightness(uint8_t level) {
  brightness = constrain(level, 0, 255);
  FastLED.setBrightness(brightness);
  FastLED.show();
  LOG_DEBUG("LED brightness set to %d", brightness);
}

CRGB LEDController::getColorForStatus(StatusColor status) {
  switch(status) {
    case StatusColor::RED:    return CRGB::Red;
    case StatusColor::GREEN:  return CRGB::Green;
    case StatusColor::BLUE:   return CRGB::Blue;
    case StatusColor::YELLOW: return CRGB::Yellow;
    case StatusColor::PURPLE: return CRGB::Purple;
    case StatusColor::WHITE:  return CRGB::White;
    case StatusColor::OFF:    return CRGB::Black;
    default:                  return CRGB::Black;
  }
}

void LEDController::setStatusLED(StatusColor color) {
  leds[LED_STATUS] = getColorForStatus(color);
}

void LEDController::setStatus(StatusColor color) {
  setStatusLED(color);
  FastLED.show();
  LOG_DEBUG("Status LED set to color %d", (int)color);
}

void LEDController::setEnergyMeter(uint8_t hours_remaining, uint8_t total_hours) {
  // Calculate how many LEDs to light up
  uint8_t leds_to_light = 0;
  if (total_hours > 0) {
    leds_to_light = (hours_remaining * LED_ENERGY_COUNT) / total_hours;
    leds_to_light = constrain(leds_to_light, 0, LED_ENERGY_COUNT);
  }
  
  // Clear energy meter LEDs first
  for (int i = 0; i < LED_ENERGY_COUNT; i++) {
    leds[LED_ENERGY_START + i] = CRGB::Black;
  }
  
  // Light up appropriate LEDs with gradient color
  for (int i = 0; i < leds_to_light; i++) {
    CRGB color;
    
    // Color gradient based on remaining energy
    if (hours_remaining >= 5) {
      color = CRGB::Green;  // Full energy
    } else if (hours_remaining >= 3) {
      color = CRGB::Yellow;  // Medium energy
    } else {
      color = CRGB::OrangeRed;  // Low energy
    }
    
    leds[LED_ENERGY_START + i] = color;
  }
  
  FastLED.show();
  LOG_DEBUG("Energy meter: %d/%d hours, %d LEDs lit", hours_remaining, total_hours, leds_to_light);
}

void LEDController::pulseStatus(StatusColor color) {
  // Breathing animation for status LED
  unsigned long now = millis();
  if (now - last_animation_time > 30) {  // Update every 30ms
    last_animation_time = now;
    
    // Calculate brightness using sine wave
    float breath = (sin(animation_step * 0.05) + 1.0) * 0.5;  // 0.0 to 1.0
    uint8_t pulse_brightness = brightness * breath;
    
    CRGB base_color = getColorForStatus(color);
    leds[LED_STATUS] = base_color;
    leds[LED_STATUS].nscale8(pulse_brightness * 255 / brightness);
    
    FastLED.show();
    animation_step++;
  }
}

void LEDController::rainbowCelebration() {
  // Congratulations! You finished your workday!
  unsigned long now = millis();
  if (now - last_animation_time > 50) {
    last_animation_time = now;
    
    for(int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV((animation_step + i * 32) % 256, 255, 255);
    }
    
    FastLED.show();
    animation_step += 5;
  }
}

void LEDController::clear() {
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

void LEDController::update() {
  // This method is called in the main loop to handle animations
  // Currently animations are triggered by specific methods
  // Could be extended for persistent animations
}
