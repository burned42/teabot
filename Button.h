#include <Arduino.h>

class Button {
  public:
    Button(int pin);
    bool isPressed();

  private:
    const int pin;
    int state;
    int lastState = LOW;
    unsigned long lastDebounceTime = 0;
    const int debounceDelay = 50;
};
