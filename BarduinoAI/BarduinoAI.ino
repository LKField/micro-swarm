#include <Arduino.h>
#include <WiFi.h>
#include "Config.h"
#include "FunctionRegistry.h"
#include "AIController.h"
#include "pitches.h"
#include <Temperature_LM75_Derived.h>
#include <ArduinoJson.h>

// Global objects
WiFiClientSecure client;
FunctionRegistry funcRegistry;
AIController* aiController;
TI_TMP102 temperature;

const int buzzerPin = 46;  // Change if needed for Arduino
const int piezoPin = 4; // The piezo sensor pin (change if needed)

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

// Variables for vibration reading and filtering
int vibrationReading = 0;
int limitedReading = 0;

String inputData;
bool isvibrating = false;


void setup() {
  Wire.begin();
  Serial.begin(115200);
      
  // Setup network
  setupWiFi();
  client.setInsecure();
  
  pinMode(buzzerPin, OUTPUT);
  pinMode(piezoPin, INPUT);

  Serial.println("Piezo vibration to note demo");

  // Initialize AI controller
  aiController = new AIController(client);
}

void playHarmonizedNotes(int note1, int note2, int note3) {
    if (note1 >= 1 && note1 <= numNotes && note2 >= 1 && note2 <= numNotes && note3 >= 1 && note3 <= numNotes) {
        int frequency1 = notes[note1 - 1];
        int frequency2 = notes[note2 - 1];
        int frequency3 = notes[note3 - 1];

        tone(buzzerPin, frequency1, 500);
        delay(600);
        tone(buzzerPin, frequency2, 500);
        delay(600);
        tone(buzzerPin, frequency3, 500);
        delay(600);
    } else {
        Serial.println("Invalid notes received");
    }
}

void readSerialAndPlayHarmonizedNotes() {
    if (Serial.available()) {
        String input = Serial.readStringUntil('\n');
        input.trim();  // Remove any leading or trailing whitespace

        if (input.startsWith("[") && input.endsWith("]")) {
            input.remove(0, 1);  // Remove the leading '['
            input.remove(input.length() - 1, 1);  // Remove the trailing ']'
            input.replace(" ", "");  // Remove any remaining spaces

            int commaIndex1 = input.indexOf(',');
            int commaIndex2 = input.indexOf(',', commaIndex1 + 1);

            if (commaIndex1 != -1 && commaIndex2 != -1) {
                int note1 = input.substring(0, commaIndex1).toInt();
                int note2 = input.substring(commaIndex1 + 1, commaIndex2).toInt();
                int note3 = input.substring(commaIndex2 + 1).toInt();

                playHarmonizedNotes(note1, note2, note3);
            } else {
                Serial.println("Invalid input format");
            }
        } else {
            Serial.println("Invalid input format");
        }
      
    }
}


String read_vibration() {
  // Average 10 readings for filtering noise
  int sum = 0;
  for (int i = 0; i < 10; i++) {
    sum += analogRead(piezoPin);
    delay(10);  // Short delay between samples for smoother reading
  }
  vibrationReading = sum / 10;  // Average of 10 readings

  Serial.println(vibrationReading);

  // Limit vibration reading to a range of 0-1023
  limitedReading = map(vibrationReading, 0, 1023, 0, numNotes - 1);

  // Play the corresponding note based on vibration
  if (vibrationReading > 200) {  // Threshold to avoid too low vibrations triggering notes
    inputData = String(limitedReading);
    isvibrating = true; 
    Serial.println("isvibrating ");
    //Serial.println(inputData);
    Serial.println(limitedReading);

  }
  delay(100);  // Short delay before next reading
  return inputData;
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
  
  // Initialize AI controller
  aiController = new AIController(client);

}

// ---------------------------------------AI RESPONSE---------------------------------------

void loop() {
  inputData = read_vibration();
  // Capture sensor data here
  //String inputData = "78";
  //Serial.printf("Input data: %s\n", inputData.c_str());

  // Get AI response
  String result;

  if(isvibrating){
    isvibrating = false;
    if (aiController->processTextData(inputData, funcRegistry.getBulletList(), result)) {
      Serial.printf("AI Response: %s\n", result.c_str());
      StaticJsonDocument<64> doc;
      DeserializationError error = deserializeJson(doc, result);
      // Check if parsing was successful
      if (error) {
        Serial.print("JSON Parsing Failed: ");
        Serial.println(error.f_str());
        return;
      }
      playHarmonizedNotes(doc[0], doc[1], doc[2]);
  } else {
      Serial.printf("AI Error: %s\n", result.c_str());
    }
  }
    
  delay(1000);

  readSerialAndPlayHarmonizedNotes();
}