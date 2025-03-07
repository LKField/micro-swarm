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
//#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include "Config.h"
#include "arduino_secrets.h"
#include "pitches.h"

// MQTT Setup names and topics 
String clientName = "Swarm_Reference";
const char* mqttClientName = clientName.c_str();
const char* topicsToPub[] = {"lab/swarm/cell1", "lab/swarm/cell2", "lab/swarm/cell3"};
const int topicsLength = 3;

WiFiClient wifiClient;
//WiFiClientSecure wifiClient;
PubSubClient mqttClient(wifiClient);

// Define frequency and message 
char* msg[] = {"440", "587", "698"};
long frequency = 0;

// debounce parameter 
bool touchBool = false;

void callback(char* topic, byte* payload, unsigned int length) {
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
      mqttClient.subscribe(topicsToPub[1]);
      Serial.print("subscribed to: ");
      Serial.println(topicsToPub[1]);

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

void setupWiFi() {
    WiFi.mode(WIFI_STA);
    Serial.printf("Connecting to %s\n", WiFiConfig::SSID);
    WiFi.begin(WiFiConfig::SSID, WiFiConfig::PASSWORD);
    
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
    }
  
    Serial.printf("\nConnected! IP: %s\n", WiFi.localIP().toString().c_str());
}

void setup()
{
  Serial.begin(19600);

  // Setup network
  setupWiFi();

  mqttClient.setServer(MQTTConfig::MQTT_BROKER, MQTTConfig::MQTT_PORT);
  mqttClient.setCallback(callback);

//  Allow the hardware to sort itself out
  delay(1500);
}

void sendData(char* data[]) {
  for (int i=0;i<topicsLength;i++) {
    mqttClient.publish(topicsToPub[i], data[i]);
  }
}

void loop()
{
  if (!mqttClient.connected()) {
    mqttConnect();
  }

  mqttClient.loop();

  int touch = touchRead(PinConfig::TOUCH_SENSOR_1);

  //Serial.println(touch);

  // debounce 
  if (touch >= 100000) {
    if (!touchBool) {
      touchBool = true;
      sendData(msg);
      // for (int i=0;i<topicsLength;i++) {
      //   mqttClient.publish(topicsToPub[i], msg[i]);
      // }
    //  Serial.println(touchBool);
    }
  } else if (touchBool){
    touchBool = false;
  }

//  Serial.println(notes[0]);
}
