#include "Knob.h"

Knob::Knob(Encoder encoder): encoder(encoder) {
  lastPosition = encoder.read();
}

int Knob::getPositionChange() {
  long newPosition = encoder.read();

  if (newPosition != lastPosition) {
    if (newPosition > lastPosition + SENSITIVITY) {
      lastPosition = newPosition;

      return 1;
    }
    
    if (newPosition < lastPosition - SENSITIVITY) {
      lastPosition = newPosition;

      return -1;
    }
  }

  return 0;
}
