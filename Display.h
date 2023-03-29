#include <Arduino.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

class Display {
  public:
    Display(Adafruit_SSD1306 display, uint8_t i2cAddress);
    void showSetup(int timerMinutes);
    void showTimer(int remainingSeconds);
    void showInProgress();
    
  private:
    Adafruit_SSD1306 display;
    const uint8_t i2cAddress;
    bool isInitialized = false;
    void initialize();
    void write(const char output[]);
};
