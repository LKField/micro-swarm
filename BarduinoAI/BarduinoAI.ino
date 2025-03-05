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

const int buzzerPin = 46;  // Change if needed for Arduino


// ---------------------------------------MUSICAL NOTES---------------------------------------


int notes[] = {
  B0, C1, CS1, D1, DS1, E1, F1, FS1, G1, GS1, A1, AS1, B1,
  C2, CS2, D2, DS2, E2, F2, FS2, G2, GS2, A2, AS2, B2,
  C3, CS3, D3, DS3, E3, F3, FS3, G3, GS3, A3, AS3, B3,
  C4, CS4, D4, DS4, E4, F4, FS4, G4, GS4, A4, AS4, B4,
  C5, CS5, D5, DS5, E5, F5, FS5, G5, GS5, A5, AS5, B5,
  C6, CS6, D6, DS6, E6, F6, FS6, G6, GS6, A6, AS6, B6,
  C7, CS7, D7, DS7, E7, F7, FS7, G7, GS7, A7, AS7, B7,
  C8, CS8, D8, DS8};

const int numNotes = sizeof(notes) / sizeof(notes[0]);
int selectedNote = 0;  // Variable to store the serial input number

void setup() {
  Wire.begin();
  Serial.begin(115200);
      
  // Setup network
  setupWiFi();
  client.setInsecure();
  
  pinMode(buzzerPin, OUTPUT);

  
  // Initialize AI controller
  aiController = new AIController(client);
}

void readSerialAndPlayTone() {
    if (Serial.available() > 0) {
        selectedNote = Serial.parseInt();  // Store the input number

        if (selectedNote >= 1 && selectedNote <= numNotes) {
            int noteIndex = selectedNote - 1;  // Adjust for array index
            int frequency = notes[noteIndex];

            Serial.print("Playing note ");
            Serial.print(selectedNote);
            Serial.print(" at ");
            Serial.print(frequency);
            Serial.println(" Hz");

            tone(buzzerPin, frequency, 300);
            delay(5);  // Small delay before next input
        } else {
            Serial.println("");
        }
    }
}



// ---------------------------------------SETUP WIFI---------------------------------------


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


// ---------------------------------------SETUP AI---------------------------------------


void setupAI() {
  Wire.begin();
  Serial.begin(115200);
      
  // Setup network
  setupWiFi();
  client.setInsecure();
  
  // Setup function registry
  //funcRegistry.attachFunction("TURN_ON_LED", turn_on_led);
  
  // Initialize AI controller
  aiController = new AIController(client);
}


// ---------------------------------------AI RESPONSE---------------------------------------


void loop() {
    // Capture sensor data here
    String inputData = "78";
    Serial.printf("Input data: %s\n", inputData.c_str());

    // Get AI response
    String result;
    
    if (aiController->processTextData(inputData, funcRegistry.getBulletList(), result)) {
        Serial.printf("AI Response: %s\n", result.c_str());
        
        if (auto func = funcRegistry.getFunctionByName(result)) {
            func();
        }
    } else {
        Serial.printf("AI Error: %s\n", result.c_str());
    }
    
    delay(5000);

    readSerialAndPlayTone();
}