#include <Arduino.h>

#include <Servo.h>

class Lift {
  public:
    Lift(Servo servo, int pin);
    void up();
    void down();

  private:
    Servo servo;
    const int pin;
    bool isInitialized = false;
    int currentPosition;
    void initialize();
    void setPosition(int position);
    static const int MIN_POSITION = 40;
    static const int MAX_POSITION = 100;
    static const int DELAY = 50;
};
