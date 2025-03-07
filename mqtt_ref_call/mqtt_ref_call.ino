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

#include "mqtt_reference.h"
#include "Config.h"
#include <WiFi.h>
//#include <WiFiClientSecure.h>

char* msg[] = {"698", "587", "440"};
bool touchBool;

//WiFiClientSecure client;
WiFiClient client;
MQTTWrapper* mqtt_wrapper;

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
  Serial.begin(19200);
  setupWiFi();
//  client.setInsecure();
  delay(1000);
  mqtt_wrapper = new MQTTWrapper(client);
  mqtt_wrapper->setupMQTT();
}

void loop() {
  mqtt_wrapper->loopMQTT();
  //  int touch = touchRead(PinConfig::TOUCH_SENSOR_1);
  int touch = touchRead(4);

  if (touch >= 100000) {
    if (!touchBool) {
      touchBool = true;
      mqtt_wrapper->sendData(msg);
    }
  } else if (touchBool) {
    touchBool = false;
  }
//  sendData(msg);
}