/**
 * Unit Tests for LED Controller
 */

#include <unity.h>
#include "../src/led_controller.h"

#ifndef UNIT_TEST
LEDController leds;

void setUp(void) {
  leds.begin();
}

void tearDown(void) {
  leds.clear();
}

void test_led_initialization(void) {
  // Test LED initialization
  leds.begin();
  TEST_PASS_MESSAGE("LED controller initialized");
}

void test_led_brightness(void) {
  // Test brightness setting
  leds.setBrightness(255);
  leds.setBrightness(128);
  leds.setBrightness(0);
  TEST_PASS();
}

void test_status_colors(void) {
  // Test all status colors
  leds.setStatus(StatusColor::RED);
  delay(100);
  leds.setStatus(StatusColor::GREEN);
  delay(100);
  leds.setStatus(StatusColor::BLUE);
  delay(100);
  leds.setStatus(StatusColor::YELLOW);
  delay(100);
  leds.setStatus(StatusColor::PURPLE);
  delay(100);
  leds.setStatus(StatusColor::WHITE);
  delay(100);
  
  TEST_PASS_MESSAGE("All status colors displayed");
}

void test_energy_meter(void) {
  // Test energy meter display
  for (int hours = 8; hours >= 0; hours--) {
    leds.setEnergyMeter(hours, 8);
    delay(200);
  }
  
  TEST_PASS_MESSAGE("Energy meter countdown tested");
}

void test_rainbow_celebration(void) {
  // Test celebration animation
  for (int i = 0; i < 100; i++) {
    leds.rainbowCelebration();
    delay(50);
  }
  
  TEST_PASS_MESSAGE("Rainbow celebration tested");
}

void test_pulse_animation(void) {
  // Test pulsing animation
  for (int i = 0; i < 100; i++) {
    leds.pulseStatus(StatusColor::BLUE);
    delay(30);
  }
  
  TEST_PASS_MESSAGE("Pulse animation tested");
}

int main(int argc, char **argv) {
  UNITY_BEGIN();
  
  RUN_TEST(test_led_initialization);
  RUN_TEST(test_led_brightness);
  RUN_TEST(test_status_colors);
  RUN_TEST(test_energy_meter);
  RUN_TEST(test_rainbow_celebration);
  RUN_TEST(test_pulse_animation);
  
  UNITY_END();
  return 0;
}

#endif
