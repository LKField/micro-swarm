#include <Arduino.h>
#include "Config.h"
#include "CameraSetup.h"
#include "DisplaySetup.h"
#include "FunctionRegistry.h"
#include "AIController.h"

// Global objects
WiFiClientSecure client;
FunctionRegistry funcRegistry;
AIController* aiController;

// LED control functions
void turn_on_led() {
    digitalWrite(PinConfig::ONBOARD_LED, HIGH);
}

void turn_off_led() {
    digitalWrite(PinConfig::ONBOARD_LED, LOW);
}

void setupWiFi() {
    WiFi.mode(WIFI_STA);
    Serial.printf("Connecting to %s\n", WiFiConfig::SSID);
    WiFi.begin(WiFiConfig::SSID, WiFiConfig::PASSWORD);
    
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        printOLED(0, "Connecting...");
        delay(500);
    }

    Serial.printf("\nConnected! IP: %s\n", WiFi.localIP().toString().c_str());
    printOLED(0, WiFi.localIP().toString());
}

void setup() {
    Serial.begin(115200);
    
    // Initialize display
    setupDisplay();
    
    // Initialize camera
    if (esp_err_t err = initCameraModule(); err != ESP_OK) {
        Serial.printf("Camera init failed: 0x%x\n", err);
        while (true) delay(1000);
    }
    
    // Setup network
    setupWiFi();
    client.setInsecure();
    
    // Initialize LED
    pinMode(PinConfig::ONBOARD_LED, OUTPUT);
    
    // Setup function registry
    funcRegistry.attachFunction("TURN_ON_LED", turn_on_led);
    funcRegistry.attachFunction("TURN_OFF_LED", turn_off_led);
    
    // Initialize AI controller
    aiController = new AIController(client);
}

void loop() {
    // Capture image
    camera_fb_t* fb = esp_camera_fb_get();
    if (!fb) {
        Serial.println("Camera capture failed");
        delay(1000);
        return;
    }
    
    // Process image
    char* base64ImageData = fbToBase64(fb);
    esp_camera_fb_return(fb);
    
    if (!base64ImageData) {
        Serial.println("Base64 conversion failed");
        delay(1000);
        return;
    }
    
    // Get AI response
    String result;
    printOLED(4, "Asking OpenAI...");
    
    if (aiController->processImage(base64ImageData, funcRegistry.getBulletList(), result)) {
        Serial.printf("AI Response: %s\n", result.c_str());
        printOLED(4, result);
        
        if (auto func = funcRegistry.getFunctionByName(result)) {
            func();
        }
    } else {
        Serial.printf("AI Error: %s\n", result.c_str());
        printOLED(4, "< Error >");
    }
    
    free(base64ImageData);
    delay(5000);
}