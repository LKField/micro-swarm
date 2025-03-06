/*
 Basic MQTT example

 This sketch demonstrates the basic capabilities of the library.
 It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic"
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary

 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.
 
*/

#include <WiFi.h>
#include <PubSubClient.h>
#include "Config.h"
#include "arduino_secrets.h"
#include "pitches.h"

// MQTT Setup names and topics 
String clientName = "Swarm_Cell_1";

const char* mqttBroker = "mqtt-staging.smartcitizen.me";
const char* mqttClientName = clientName.c_str();
const char* mqttUser = "fablabbcn102";
const char* mqttPass = "";
const char* topicToSub = "lab/swarm/cell1";

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  tone(PinConfig::BUZZER, 440, 500);
}

void mqttConnect() {
  // Loop until we're reconnected
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (mqttClient.connect(mqttClientName, mqttUser, mqttPass)) {
      Serial.println("connected");

      // Subscribing
      mqttClient.subscribe(topicToSub);
      Serial.print("subscribed to: ");
      Serial.println(topicToSub);

      // Publishing 
      // mqttClient.publish(topicToPub, "hello there!");
      // Serial.print("published to: ");
      // Serial.println(topicToPub);

    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 1 second");
      // Wait 1 seconds before retrying
      delay(1000);
    }
  }
}

void setupWiFi() {
    WiFi.mode(WIFI_STA);
    Serial.printf("Connecting to %s\n", WiFiConfig::SSID);
    WiFi.begin(WiFiConfig::SSID, WiFiConfig::PASSWORD);
    
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
    }
  
    Serial.printf("\nConnected! IP: %s\n", WiFi.localIP().toString().c_str());
    tone(PinConfig::BUZZER, 440, 500);
    noTone(PinConfig::BUZZER);
}

void setup()
{
  Serial.begin(9600);

  // Setup network
  setupWiFi();

  // Set up MQTT 
  mqttClient.setServer(mqttBroker, 1883);
  mqttClient.setCallback(callback);

  // Set up Buzzer 
  //pinMode(PinConfig::BUZZER, OUTPUT);

  // Allow the hardware to sort itself out
  delay(1500);
}

void loop()
{
  if (!mqttClient.connected()) {
    mqttConnect();
  }
  mqttClient.loop();
}
