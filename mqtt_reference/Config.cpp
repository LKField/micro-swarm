// config.cpp
#include "Config.h"
#include "arduino_secrets.h"

// WiFi Configuration definitions
const char* WiFiConfig::SSID = SECRET_SSID;
const char* WiFiConfig::PASSWORD = SECRET_PASS;

// Hardware Configuration definitions
const int PinConfig::ONBOARD_LED = 48; 
const int PinConfig::BUZZER = 46;           // Changed to buzzer pin 46 not 43
const int PinConfig::NEOPIXEL = 38;
const int PinConfig::TOUCH_SENSOR_1 = 6;

// To connect to the Fab Lab BCN server 
const char* MQTTConfig::MQTT_BROKER = SECRET_MQTT_BROKER;
const int MQTTConfig::MQTT_PORT = SECRET_MQTT_PORT;
const char* MQTTConfig::MQTT_USER = SECRET_MQTT_USER;
const char* MQTTConfig::MQTT_PASS = SECRET_MQTT_PASS;
