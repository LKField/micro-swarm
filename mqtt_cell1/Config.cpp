// config.cpp
#include "Config.h"
#include "arduino_secrets.h"

// WiFi Configuration definitions
const char* WiFiConfig::SSID = SECRET_SSID;
const char* WiFiConfig::PASSWORD = SECRET_PASS;

// Hardware Configuration definitions
const int PinConfig::ONBOARD_LED = 48; 
const int PinConfig::BUZZER = 14;           // For Barduino 4.0.1 Buzzer pin is 14. Barduino 4.0.2 Buzzer pin is 46
const int PinConfig::NEOPIXEL = 38;