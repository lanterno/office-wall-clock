/**
 * Button Handler - Debouncing and event detection
 */

#ifndef BUTTON_HANDLER_H
#define BUTTON_HANDLER_H

#include <Arduino.h>
#include "config.h"
#include "types.h"

class ButtonHandler {
private:
  uint8_t pin;
  bool last_state;
  bool current_state;
  unsigned long last_debounce_time;
  unsigned long press_start_time;
  bool long_press_triggered;
  
public:
  ButtonHandler(uint8_t button_pin);
  void begin();
  ButtonEvent update();
  bool isPressed();
};

#endif // BUTTON_HANDLER_H
