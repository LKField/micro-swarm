#include <Arduino.h>
#include <WiFi.h>
#include "Config.h"
#include "FunctionRegistry.h"
#include "AIController.h"
#include "pitches.h"
#include <Temperature_LM75_Derived.h>

// Global objects
WiFiClientSecure client;
FunctionRegistry funcRegistry;
AIController* aiController;
TI_TMP102 temperature;

// LED control functions
String turn_on_led() {
    digitalWrite(PinConfig::ONBOARD_LED, HIGH);
}

String turn_off_led() {
    digitalWrite(PinConfig::ONBOARD_LED, LOW);
}

// Light sensor functions
String read_room_light() {
  return String(analogRead(PinConfig::PHOTO_TRANSISTOR));
}

// Temperature sensor functions
String read_room_temperature() {
  return String(temperature.readTemperatureC());
}

// Buzzer functions
String play_melody() {
  tone(PinConfig::BUZZER, NOTE_C3, 8);
}

String melody_01() {
  Serial.println("melody 01");
  for (int i = 0; i < 3; i++) {
    tone(PinConfig::BUZZER, NOTE_C2, 500);
    //delay(1000);
    //noTone(PinConfig::BUZZER);
    delay(1000);
  }
  Serial.println("melody 01 - done");
  return "";
}

String melody_02() {
  Serial.println("melody 02");
  for (int i = 0; i < 3; i++) {
    tone(PinConfig::BUZZER, NOTE_C4, 500);
    //delay(1000);
    //noTone(PinConfig::BUZZER);
    delay(1000);
  }
  Serial.println("melody 02 - done");
  return "";
}

String melody_03() {
  Serial.println("melody 03");
  for (int i = 0; i < 3; i++) {
    tone(PinConfig::BUZZER, NOTE_C5, 500);
    //delay(1000);
    //noTone(PinConfig::BUZZER);
    delay(1000);
  }
  Serial.println("melody 03 - done");
  return "";
}

String melody_04() {
  Serial.println("melody 04");
  for (int i = 0; i < 3; i++) {
    tone(PinConfig::BUZZER, NOTE_C6, 500);
    //delay(1000);
    //noTone(PinConfig::BUZZER);
    delay(1000);
  }
  Serial.println("melody 04 - done");
  return "";
}

String melody_05() {
  Serial.println("melody 05");
  for (int i = 0; i < 3; i++) {
    tone(PinConfig::BUZZER, NOTE_C8, 500);
    //delay(1000);
    //noTone(PinConfig::BUZZER);
    delay(1000);
  }
  Serial.println("melody 05 - done");
  return "";
}

void setupWiFi() {
    WiFi.mode(WIFI_STA);
    Serial.printf("Connecting to %s\n", WiFiConfig::SSID);
    WiFi.begin(WiFiConfig::SSID, WiFiConfig::PASSWORD);
    
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }

    Serial.printf("\nConnected! IP: %s\n", WiFi.localIP().toString().c_str());
}

void setup() {
  Wire.begin();
  Serial.begin(115200);
      
  // Setup network
  setupWiFi();
  client.setInsecure();
  
  // Init LED
 // pinMode(PinConfig::ONBOARD_LED, OUTPUT);
  // Init photo transistor
  pinMode(PinConfig::PHOTO_TRANSISTOR, INPUT);

  
  // Setup function registry
//  funcRegistry.attachFunction("TURN_ON_LED", turn_on_led);
//  funcRegistry.attachFunction("TURN_OFF_LED", turn_off_led);
//  funcRegistry.attachFunction("PLAY_MELODY", play_melody);
  funcRegistry.attachFunction("PLAY_MELODY_GLOOMY", melody_01);
  funcRegistry.attachFunction("PLAY_MELODY_SAD", melody_02);
  funcRegistry.attachFunction("PLAY_MELODY_NEUTRAL", melody_03);
  funcRegistry.attachFunction("PLAY_MELODY_HAPPY", melody_04);
  funcRegistry.attachFunction("PLAY_MELODY_EXCITED", melody_05);

  
  // Initialize AI controller
  aiController = new AIController(client);
}

void loop() {
    // Capture sensor data here
    String inputData = "Room light: " + read_room_light() + ", Room temperature: " + read_room_temperature();
    Serial.printf("Input data: %s\n", inputData.c_str());

    // Get AI response
    String result;

    
    if (aiController->processTextData(inputData, funcRegistry.getBulletList(), result)) {
        Serial.printf("AI Response: %s\n", result.c_str());
        
        if (auto func = funcRegistry.getFunctionByName(result)) {
            Serial.print("FUNCTION");
            Serial.println(result);
            func();
        }
    } else {
        Serial.printf("AI Error: %s\n", result.c_str());
    }
    
    delay(1000);
}