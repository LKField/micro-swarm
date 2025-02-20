// config.h - Central configuration file
#ifndef CONFIG_H
#define CONFIG_H

// WiFi Configuration
struct WiFiConfig {
    static const char* SSID;
    static const char* PASSWORD;
};

// OpenAI Configuration
struct OpenAIConfig {
    static const char* API_KEY;
    static const char* MODEL;
    static const int MAX_CALLS;
    static const int MAX_TOKENS;
    static const char* BASE_PROMPT;
    static const char* GOAL;
};

// Hardware Configuration
struct PinConfig {
    static const int ONBOARD_LED;
    static const int PHOTO_TRANSISTOR;
    static const int BUZZER;
    static const int TEMP_SENSOR_SDA;
    static const int TEMP_SENSOR_SCL;
    static const int NEOPIXEL;
};

#endif