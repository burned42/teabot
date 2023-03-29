#include <Arduino.h>

class Timer {
  public:
    Timer(int duration);
    int getRemainingSeconds();
    void updateRemainingSeconds(int difference);
    void tick();
    void start();
    void reset();
    bool isRunning();

  private:
    const int defaultDuration;
    int remainingSeconds;
    bool _isRunning = false;
    unsigned long lastUpdateMs;
};
