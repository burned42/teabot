#include "Display.h"

Display::Display(Adafruit_SSD1306 display, uint8_t i2cAddress): display(display), i2cAddress(i2cAddress) {
}

void Display::initialize() {
  if (isInitialized) {
    return;
  }

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, i2cAddress)) {
    for(;;); // Don't proceed, loop forever
  }

  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(3);

  display.clearDisplay();
  display.setRotation(2);
  display.display();

  isInitialized = true;
}

void Display::write(const char output[]) {
  initialize();

  display.clearDisplay();
  display.setCursor(0, 0);

  display.print(output);

  display.display();
}

void Display::showSetup(int timerMinutes) {
  char output[7];
  sprintf(output, "%3d min", timerMinutes);

  write(output);
}

void Display::showTimer(int remainingSeconds) {
  char output[7];
  int minutes = remainingSeconds / 60;
  int seconds = remainingSeconds % 60;
  sprintf(output, "T %02d:%02d", minutes, seconds);

  write(output);
}

void Display::showInProgress() {
  write("  ...");  
}
