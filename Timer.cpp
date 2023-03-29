#include "Timer.h"

Timer::Timer(int duration): defaultDuration(duration) {
  remainingSeconds = defaultDuration;
}

int Timer::getRemainingSeconds() {
  return remainingSeconds;
}

void Timer::updateRemainingSeconds(int difference) {
  remainingSeconds += difference;

  if (remainingSeconds < 0) {
    remainingSeconds = 0;
  }
}

void Timer::tick() {
  if (!_isRunning) {
    return;
  }

  if (lastUpdateMs + 1000 <= millis()) {
    lastUpdateMs += 1000;
    remainingSeconds--;

    if (remainingSeconds <= 0) {
      reset();
    }
  }
}

void Timer::start() {
  _isRunning = true;
  lastUpdateMs = millis();
}

void Timer::reset() {
  remainingSeconds = defaultDuration;
  _isRunning = false;
}

bool Timer::isRunning() {
  return _isRunning;
}
