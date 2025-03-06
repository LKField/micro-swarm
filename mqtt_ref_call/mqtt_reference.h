#ifndef MQTT_REFERENCE_H
#define MQTT_REFERENCE_H

#include <WiFi.h>
#include <PubSubClient.h>
#include "Config.h"
#include "arduino_secrets.h"
#include "pitches.h"

// Define the MQTTClient class
class MQTTWrapper {
  public:
    // Constructor to initialize the MQTT client with necessary parameters
    MQTTWrapper(WiFiClient& wifiClient);

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

    const char** topicsToPub;


    // Helper functions for MQTT
    void setupMQTT();
    void loopMQTT();
    void mqttConnect();
    void callback(char* topic, byte* payload, unsigned int length);
    void sendData(char* data[]);


    // Message to be sent
//    char* msg[3] = {"440", "587", "698"};
};

#endif

