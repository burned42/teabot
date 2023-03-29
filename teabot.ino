#include "Button.h"
#include "Knob.h"
#include "Timer.h"
#include "Display.h"
#include "Lift.h"

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

// Arduino Nano Pins
#define D3 3
#define D5 5
#define D6 6
#define D7 8

#define BUTTON_PIN D3
Button button(BUTTON_PIN);

#define ENCODER_PIN1 D5
#define ENCODER_PIN2 D6
Encoder encoder(ENCODER_PIN1, ENCODER_PIN2);
Knob knob(encoder);

#define TIMER_DEFAULT_MINUTES 7
Timer timer(TIMER_DEFAULT_MINUTES * 60);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C // 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 _display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Display display(_display, SCREEN_ADDRESS);

#define SERVO_PIN D7
Servo servo;
Lift lift(servo, SERVO_PIN);

const int stateSetup = 0;
const int stateTimerRunning = 1;
int state = stateSetup;

void setup() {
  Serial.begin(9600);
  Serial.println("teabot");

  lift.up();
}

void loop() {
  updateTimerFromInput();
  updateTimer();
  updateDisplay();

  if (button.isPressed()) {
    Serial.println("button");
    handleButtonPress();
  }

  delay(10);
}

void updateTimerFromInput() {
  int knobChange = knob.getPositionChange();

  if (knobChange == 1) {
    timer.updateRemainingSeconds(60);
    Serial.println("increase");
  } else if (knobChange == -1) {
    if (timer.getRemainingSeconds() > 60) {
      timer.updateRemainingSeconds(-60);
      Serial.println("decrease");
    }
  }
}

void updateTimer() {
  timer.tick();

  if (state == stateTimerRunning && !timer.isRunning()) {
    endProcess();
  }
}

void updateDisplay() {
  if (state == stateSetup) {
    display.showSetup(timer.getRemainingSeconds() / 60);
  } else if (state == stateTimerRunning) {
    display.showTimer(timer.getRemainingSeconds());
  }
}

void handleButtonPress() {
  if (state == stateSetup) {
    startProcess();
  } else if (state == stateTimerRunning) {
    endProcess();
  }
}

void startProcess() {
  display.showInProgress();

  lift.down();
  delay(2000);
  lift.up();
  lift.down();

  timer.start();
  state = stateTimerRunning;
}

void endProcess() {
  display.showInProgress();

  lift.up();
  delay(500);
  lift.down();
  delay(1000);
  lift.up();

  timer.reset();
  state = stateSetup;
}
