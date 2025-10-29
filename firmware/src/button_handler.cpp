/**
 * Button Handler - Implementation
 */

#include "button_handler.h"

ButtonHandler::ButtonHandler(uint8_t button_pin) 
  : pin(button_pin), 
    last_state(HIGH), 
    current_state(HIGH),
    last_debounce_time(0),
    press_start_time(0),
    long_press_triggered(false) {
}

void ButtonHandler::begin() {
  pinMode(pin, INPUT_PULLUP);  // Use internal pull-up resistor
  current_state = digitalRead(pin);
  last_state = current_state;
  LOG_INFO("Button handler initialized on pin %d", pin);
}

ButtonEvent ButtonHandler::update() {
  int reading = digitalRead(pin);
  ButtonEvent event = ButtonEvent::NONE;
  
  // Check if button state changed
  if (reading != last_state) {
    last_debounce_time = millis();
  }
  
  // Debounce check
  if ((millis() - last_debounce_time) > BUTTON_DEBOUNCE_MS) {
    // State has been stable for debounce time
    if (reading != current_state) {
      current_state = reading;
      
      if (current_state == LOW) {
        // Button pressed (active low)
        press_start_time = millis();
        long_press_triggered = false;
        event = ButtonEvent::PRESSED;
        LOG_DEBUG("Button pressed");
      } else {
        // Button released
        if (!long_press_triggered) {
          event = ButtonEvent::RELEASED;
          LOG_DEBUG("Button released");
        }
      }
    }
  }
  
  // Check for long press
  if (current_state == LOW && !long_press_triggered) {
    if ((millis() - press_start_time) > BUTTON_LONG_PRESS_MS) {
      long_press_triggered = true;
      event = ButtonEvent::LONG_PRESS;
      LOG_INFO("Button long press detected");
    }
  }
  
  last_state = reading;
  return event;
}

bool ButtonHandler::isPressed() {
  return current_state == LOW;
}
