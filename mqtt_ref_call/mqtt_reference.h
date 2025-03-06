#ifndef MQTT_REFERENCE_H
#define MQTT_REFERENCE_H

#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include "Config.h"
#include "arduino_secrets.h"
#include "pitches.h"

// Define the MQTTClient class
class MQTTWrapper {
  public:
    // Constructor to initialize the MQTT client with necessary parameters
  //  MQTTWrapper(WiFiClientSecure& wifiClient);
    MQTTWrapper(WiFiClient& wifiClient);

    
    // These methods should be public to be called from main sketch
    void setupMQTT();
    void loopMQTT();
    void sendData(char* data[]);

  private:
    // MQTT Client configuration
    const char* mqttBroker;
    const char* mqttClientName;
    const char* mqttUser;
    const char* mqttPass;
    int topicsLength;
    
    // MQTT object
    PubSubClient mqttClient;

    // Internal state variables
    long frequency;

    // MQTT topics 
    const char* topicsToPub[3];

    // Helper functions for MQTT
    void mqttConnect();
    void callback(char* topic, byte* payload, unsigned int length);
};

#endif
