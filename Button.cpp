#include "Button.h"

Button::Button(int pin): pin(pin) {
  pinMode(pin, INPUT_PULLUP);
}

bool Button::isPressed() {
  int reading = digitalRead(pin);

  if (reading != lastState) {
    lastDebounceTime = millis();
    lastState = reading;
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != state) {
      state = reading;

      if (state == LOW) {
        return true;
      }
    }
  }

  return false;
}
