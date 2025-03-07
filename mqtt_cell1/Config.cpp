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

// To connect to the Fab Lab BCN server 
const char* MQTTConfig::MQTT_BROKER = SECRET_MQTT_BROKER;
const int MQTTConfig::MQTT_PORT = SECRET_MQTT_PORT;
const char* MQTTConfig::MQTT_USER = SECRET_MQTT_USER;
const char* MQTTConfig::MQTT_PASS = SECRET_MQTT_PASS;
