// For the OLED Display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ESP32-CAM doesn't have dedicated i2c pins, so we define our own. Let's choose 15 and 14
#define I2C_SDA 15
#define I2C_SCL 14
TwoWire I2Cbus = TwoWire(0);

// Display defines
#define SCREEN_WIDTH    128
#define SCREEN_HEIGHT   64
#define OLED_RESET      -1
#define SCREEN_ADDRESS  0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &I2Cbus, OLED_RESET);

#define LINE_HEIGHT 8

void setupDisplay() {
  // Initialize I2C with our defined pins
  I2Cbus.begin(I2C_SDA, I2C_SCL, 100000);
  Serial.println("Initialize display");

  // Dont continue unless we can connect to the OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.printf("SSD1306 OLED display failed to initalize.\nCheck that display SDA is connected to pin %d and SCL connected to pin %d\n", I2C_SDA, I2C_SCL);
    while (true);
  }

  // Display settings
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}

void clearLine(int line) {
  // Calculate the y-coordinate for the given line number (line 0 is the top)
  int y = line * LINE_HEIGHT;
  // Clear the desired line by drawing a filled rectangle with the background color.
  display.fillRect(0, y, display.width(), LINE_HEIGHT, SSD1306_BLACK);
  display.display();
}

void printOLED(int line, String text) {
  int y = line * LINE_HEIGHT;
  display.clearDisplay();
  display.setCursor(0, y);
  display.print(text);
  display.display();
}
