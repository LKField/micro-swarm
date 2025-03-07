// config.h - Central configuration file
#ifndef CONFIG_H
#define CONFIG_H

// WiFi Configuration
struct WiFiConfig {
    static const char* SSID;
    static const char* PASSWORD;
};

// Hardware Configuration
struct PinConfig {
    static const int ONBOARD_LED;
    static const int BUZZER;
    static const int NEOPIXEL;
    static const int TOUCH_SENSOR_1;
};

// MQTT Configuration
struct MQTTConfig {
  static const char* MQTT_BROKER;
  static const int MQTT_PORT;
  static const char* MQTT_USER;
  static const char* MQTT_PASS;
};

#endif