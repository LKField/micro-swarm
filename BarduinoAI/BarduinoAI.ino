#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "Config.h"
#include "FunctionRegistry.h"
#include "AIController.h"
#include "pitches.h"
#include <Temperature_LM75_Derived.h>
#include <ArduinoJson.h>

// Global objects
WiFiClientSecure client;
PubSubClient mqttClient(client);
FunctionRegistry funcRegistry;
AIController* aiController;
TI_TMP102 temperature;

// MQTT Setup names and topics 
String clientName = "Swarm_Reference";
const char* mqttClientName = clientName.c_str();
const char* topicsToPub[] = {"lab/swarm/cell1", "lab/swarm/cell2", "lab/swarm/cell3"};
const int topicsLength = 3;

// Define frequency and message 
char* msg[] = {"440", "587", "698"};
long frequency = 0;

//const int buzzerPin = 46;  // Change if needed for Arduino
//const int piezoPin = 4; // The piezo sensor pin (change if needed)

// ---------------------------------------MUSICAL NOTES---------------------------------------

char* notes[] = {
  B0, C1, CS1, D1, DS1, E1, F1, FS1, G1, GS1, A1, AS1, B1,
  C2, CS2, D2, DS2, E2, F2, FS2, G2, GS2, A2, AS2, B2,
  C3, CS3, D3, DS3, E3, F3, FS3, G3, GS3, A3, AS3, B3,
  C4, CS4, D4, DS4, E4, F4, FS4, G4, GS4, A4, AS4, B4,
  C5, CS5, D5, DS5, E5, F5, FS5, G5, GS5, A5, AS5, B5,
  C6, CS6, D6, DS6, E6, F6, FS6, G6, GS6, A6, AS6, B6,
  C7, CS7, D7, DS7, E7, F7, FS7, G7, GS7, A7, AS7, B7,
  C8, CS8, D8, DS8};

// int notes[] = {
//   B0, C1, CS1, D1, DS1, E1, F1, FS1, G1, GS1, A1, AS1, B1,
//   C2, CS2, D2, DS2, E2, F2, FS2, G2, GS2, A2, AS2, B2,
//   C3, CS3, D3, DS3, E3, F3, FS3, G3, GS3, A3, AS3, B3,
//   C4, CS4, D4, DS4, E4, F4, FS4, G4, GS4, A4, AS4, B4,
//   C5, CS5, D5, DS5, E5, F5, FS5, G5, GS5, A5, AS5, B5,
//   C6, CS6, D6, DS6, E6, F6, FS6, G6, GS6, A6, AS6, B6,
//   C7, CS7, D7, DS7, E7, F7, FS7, G7, GS7, A7, AS7, B7,
//   C8, CS8, D8, DS8};

const int numNotes = sizeof(notes) / sizeof(notes[0]);

// Variables for vibration reading and filtering
int vibrationReading = 0;
int limitedReading = 0;

String inputData;
bool isvibrating = false;

// ---------------------------------------MQTT FUNCTIONS---------------------------------------

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  frequency = 0;
  for (int i=0;i<length;i++) {
  //  Serial.print((char)payload[i]);
    int digit = (char)payload[i] - '0';
    frequency = frequency * 10 + digit;
  }
  Serial.print("Frequency: ");
  Serial.print(frequency);
  tone(PinConfig::BUZZER, frequency, 500);
  Serial.println();
}

void mqttConnect() {
  // Loop until we're reconnected
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (mqttClient.connect(mqttClientName, MQTTConfig::MQTT_USER, MQTTConfig::MQTT_PASS)) {
      Serial.println("connected");

      // Subscribing to topicsToPub[1] = "lab/swarm/cell2"
      mqttClient.subscribe(topicsToPub[0]);
      Serial.print("subscribed to: ");
      Serial.println(topicsToPub[0]);

      // Publishing to all topics in topicsToPub[]
      for (int i=0;i<topicsLength;i++) {
        mqttClient.publish(topicsToPub[i], "440");
        Serial.print("published to: ");
       Serial.println(topicsToPub[i]);
       }
      
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 1 second");
      // Wait 1 seconds before retrying
      delay(1000);
    }
  }
//  Serial.println("End of mqttConnect");
}

void mqttSendData(char* data[]) {
  for (int i=0;i<topicsLength;i++) {
    mqttClient.publish(topicsToPub[i], data[i]);
  }
}

// ---------------------------------------MUSICAL FUNCTIONS---------------------------------------
// void sendHarmonizedNotes(int data1, int data2, int data3) {
// //  char* data[3];
//   Serial.println(data1);
//   Serial.println(data2);
//   Serial.println(data3);
//   char* notesForPub[3] = {0, 0, 0};
//   notesForPub[0] = notes[data1 - 1];
//   notesForPub[1] = notes[data2 - 1];
//   notesForPub[2] = notes[data3 - 1];

//   Serial.print("notesForPub[0]: ");
//   Serial.println(notesForPub[0]);
//   mqttSendData(notesForPub);
//  return notesForPub;
//}
char** sendHarmonizedNotes(int data1, int data2, int data3) {
//  char* data[3];
  Serial.println(data1);
  Serial.println(data2);
  Serial.println(data3);
  char* notesForPub[3] = {0, 0, 0};
  notesForPub[0] = notes[data1 - 1];
  notesForPub[1] = notes[data2 - 1];
  notesForPub[2] = notes[data3 - 1];

  Serial.print("notesForPub[0]: ");
  Serial.println(notesForPub[0]);
//  mqttSendData(notesForPub);

  return notesForPub;
}
// void sendHarmonizedNotes(int data[]) {
// //  char* data[3];
//   Serial.println(data);
//   char* notesForPub[3];
//   for (int i = 0; i < 10; i++) {
//     notesForPub[i] = notes[data[i] - 1];
//   }
// //  Serial.println(data);
//   mqttSendData(notesForPub);
// }

// void playHarmonizedNotes(int note1, int note2, int note3) {
//     if (note1 >= 1 && note1 <= numNotes && note2 >= 1 && note2 <= numNotes && note3 >= 1 && note3 <= numNotes) {
//         int frequency1 = notes[note1 - 1];
//         int frequency2 = notes[note2 - 1];
//         int frequency3 = notes[note3 - 1];

//         tone(PinConfig::BUZZER, frequency1, 500);
//         delay(600);
//         tone(PinConfig::BUZZER, frequency2, 500);
//         delay(600);
//         tone(PinConfig::BUZZER, frequency3, 500);
//         delay(600);
//     } else {
//         Serial.println("Invalid notes received");
//     }
// }

// void readSerialAndPlayHarmonizedNotes() {
//     if (Serial.available()) {
//         String input = Serial.readStringUntil('\n');
//         input.trim();  // Remove any leading or trailing whitespace

//         if (input.startsWith("[") && input.endsWith("]")) {
//             input.remove(0, 1);  // Remove the leading '['
//             input.remove(input.length() - 1, 1);  // Remove the trailing ']'
//             input.replace(" ", "");  // Remove any remaining spaces

//             int commaIndex1 = input.indexOf(',');
//             int commaIndex2 = input.indexOf(',', commaIndex1 + 1);

//             if (commaIndex1 != -1 && commaIndex2 != -1) {
//                 int note1 = input.substring(0, commaIndex1).toInt();
//                 int note2 = input.substring(commaIndex1 + 1, commaIndex2).toInt();
//                 int note3 = input.substring(commaIndex2 + 1).toInt();

//                 playHarmonizedNotes(note1, note2, note3);
//             } else {
//                 Serial.println("Invalid input format");
//             }
//         } else {
//             Serial.println("Invalid input format");
//         }
      
//     }
// }

// ---------------------------------------VIBRATION FUNCTION---------------------------------------
String read_vibration() {
  // Average 10 readings for filtering noise
  int sum = 0;
  for (int i = 0; i < 10; i++) {
    sum += analogRead(PinConfig::VIBRATION);
    delay(10);  // Short delay between samples for smoother reading
  }
  vibrationReading = sum / 10;  // Average of 10 readings

//  Serial.println(vibrationReading);

  // Limit vibration reading to a range of 0-1023
  limitedReading = map(vibrationReading, 0, 1023, 0, numNotes - 1);

  // Play the corresponding note based on vibration
  if (vibrationReading > 200) {  // Threshold to avoid too low vibrations triggering notes
    inputData = String(limitedReading);
    isvibrating = true; 
    Serial.println("isvibrating ");
    //Serial.println(inputData);
  //  Serial.println(limitedReading);

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

// ---------------------------------------SETUP---------------------------------------

void setup() {
  Wire.begin();
  Serial.begin(115200);
      
  // Setup network
  setupWiFi();
  client.setInsecure();

  // Setup MQTT
  mqttClient.setServer(MQTTConfig::MQTT_BROKER, MQTTConfig::MQTT_PORT);
  mqttClient.setCallback(mqttCallback);

  // Initialize AI controller
  aiController = new AIController(client);
  
//  pinMode(buzzerPin, OUTPUT);
//  pinMode(piezoPin, INPUT);

//  Serial.println("Piezo vibration to note demo");
  



}

// ---------------------------------------MAIN LOOP---------------------------------------

void loop() {
  bool notes_flag = false;
  char** notes[3];
  //int doc[3] = {0,0,0};
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
    //  playHarmonizedNotes(doc[0], doc[1], doc[2]);
      notes[] = sendHarmonizedNotes(doc[0], doc[1], doc[2]);

    //  sendHarmonizedNotes(doc[0], doc[1], doc[2]);
    //  sendHarmonizedNotes(doc);
      notes_flag = true;
    } else {
      Serial.printf("AI Error: %s\n", result.c_str());
    }
  } else { 
    if (!mqttClient.connected()) {
      mqttConnect();
    }
    if (notes_flag) {
      notes_flag = false;
      mqttSendData(notes);
    }
    
    mqttClient.loop();
    
//  readSerialAndPlayHarmonizedNotes();
  }
  delay(1000);
}