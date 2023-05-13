#include <Arduino.h>

#define ENCODER_DO_NOT_USE_INTERRUPTS
#include <Encoder.h>

class Knob {
  public:
    Knob(Encoder encoder);
    int getPositionChange();

  private:
    Encoder encoder;
    long lastPosition;
    static const int SENSITIVITY = 2;
};
