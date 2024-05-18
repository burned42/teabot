#include "Lift.h"

Lift::Lift(Servo servo, int pin): servo(servo), pin(pin) {
}

void Lift::initialize() {
  if (isInitialized) {
    return;
  }

  servo.attach(pin);

  currentPosition = MAX_POSITION;
  servo.write(currentPosition);

  isInitialized = true;
}

void Lift::up() {
  setPosition(MAX_POSITION);
}

void Lift::down() {
  setPosition(MIN_POSITION);
}

void Lift::setPosition(int position) {
  initialize();

  position = min(position, MAX_POSITION);
  position = max(position, MIN_POSITION);

  do {
    if (currentPosition < position) {
      currentPosition++;
    } else if (currentPosition > position) {
      currentPosition--;
    }

    servo.write(currentPosition);
    delay(DELAY);
  } while (currentPosition != position);
}
