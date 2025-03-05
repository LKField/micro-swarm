#include <ArduinoMqttClient.h>
#include <WiFi.h>
#include <Adafruit_NeoPixel.h>
#include "Config.h"
#include "arduino_secrets.h"

//WiFiClientSecure wifiClient;    // TODO: Figure out why WiFiClientSecure is not working 
WiFiClient wifiClient; 
MqttClient mqttClient(wifiClient);

const char broker[] = "test.mosquitto.org";
int        port     = 1883;
const char topic[]  = "real_unique_topic";
const char topic2[]  = "real_unique_topic_2";
const char topic3[]  = "real_unique_topic_3";

//set interval for sending messages (milliseconds)
const long interval = 8000;
unsigned long previousMillis = 0;

int count = 0;

Adafruit_NeoPixel pixels(1, PinConfig::NEOPIXEL, NEO_GRB + NEO_KHZ800);


String notes[] = {"C4", "D4", "E4", "F4", "G4"};
String notes2[] = {"E4", "G4", "A5", "C5", "E5"};
String notes3[] = {"A5", "C5", "E5", "G5", "A6"};

void setupWiFi() {
    WiFi.mode(WIFI_STA);
  //  Serial.printf("Connecting to %s\n", WiFiConfig::SSID);
    WiFi.begin(WiFiConfig::SSID, WiFiConfig::PASSWORD);
    
    while (WiFi.status() != WL_CONNECTED) {
    //    Serial.print(".");
      pixels.setPixelColor(0, pixels.Color(255, 0, 0));
      pixels.show();  // Send the updated pixel colors to the hardware.
      digitalWrite(PinConfig::ONBOARD_LED, HIGH);  // turn the LED on (HIGH is the voltage level)
      delay(250);
      digitalWrite(PinConfig::ONBOARD_LED, LOW);   // turn the LED off by making the voltage LOW
      delay(250);
    }
  
    digitalWrite(PinConfig::ONBOARD_LED, HIGH);  // turn the LED on (HIGH is the voltage level)

  //  Serial.printf("\nConnected! IP: %s\n", WiFi.localIP().toString().c_str());
}


void setup() {
  //Initialize serial and wait for port to open:
 Serial.begin(9600);
 while (!Serial) {
   ; // wait for serial port to connect. Needed for native USB port only
 }

  // attempt to connect to Wifi network:
//  Serial.print("Attempting to connect to WPA SSID: ");
//  Serial.println(WiFiConfig::SSID);

  // Set up LEDs
  pinMode(PinConfig::ONBOARD_LED, OUTPUT);
  pixels.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)


  // Setup network
  setupWiFi();
  //client.setInsecure();     // TODO: Figure out why WiFiClientSecure is not working 


//  Serial.println("You're connected to the network");
//  Serial.println();

//  Serial.print("Attempting to connect to the MQTT broker: ");
//  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
  //  Serial.print("MQTT connection failed! Error code = ");
  //  Serial.println(mqttClient.connectError());

    pixels.setPixelColor(0, pixels.Color(0, 255, 0));
    pixels.show();  // Send the updated pixel colors to the hardware.
    digitalWrite(PinConfig::ONBOARD_LED, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(250);
    digitalWrite(PinConfig::ONBOARD_LED, LOW);   // turn the LED off by making the voltage LOW
    delay(250);

    while (1);
  }

  digitalWrite(PinConfig::ONBOARD_LED, HIGH);  // turn the LED on (HIGH is the voltage level)

//  Serial.println("You're connected to the MQTT broker!");
//  Serial.println();
}

void loop() {
  // call poll() regularly to allow the library to send MQTT keep alive which
  // avoids being disconnected by the broker
  mqttClient.poll();

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time a message was sent
    previousMillis = currentMillis;

    //record random value from A0, A1 and A2
    // int Rvalue = analogRead(A0);
    // int Rvalue2 = analogRead(A1);
    // int Rvalue3 = analogRead(A2);

    //notes to send 
    String Rvalue = "C4";
    String Rvalue2 = "E4";
    String Rvalue3 = "A5";


    Serial.print("Sending message to topic: ");
    Serial.println(topic);
    Serial.println(Rvalue);

    Serial.print("Sending message to topic: ");
    Serial.println(topic2);
    Serial.println(Rvalue2);

    Serial.print("Sending message to topic: ");
    Serial.println(topic2);
    Serial.println(Rvalue3);

    // Neopixel to a color for "sending messages"
    pixels.setPixelColor(0, pixels.Color(150, 150, 150));
    pixels.show();  // Send the updated pixel colors to the hardware.

    // send message, the Print interface can be used to set the message contents
    mqttClient.beginMessage(topic);
    mqttClient.print(Rvalue);
    mqttClient.endMessage();
    digitalWrite(PinConfig::ONBOARD_LED, HIGH);  // turn the LED on (HIGH is the voltage level)


    mqttClient.beginMessage(topic2);
    mqttClient.print(Rvalue2);
    mqttClient.endMessage();
    digitalWrite(PinConfig::ONBOARD_LED, LOW);  // turn the LED on (HIGH is the voltage level)


    mqttClient.beginMessage(topic3);
    mqttClient.print(Rvalue3);
    mqttClient.endMessage();
    digitalWrite(PinConfig::ONBOARD_LED, HIGH);  // turn the LED on (HIGH is the voltage level)


    delay(500);
    digitalWrite(PinConfig::ONBOARD_LED, LOW);  // turn the LED on (HIGH is the voltage level)

  //  Serial.println();
  }
}