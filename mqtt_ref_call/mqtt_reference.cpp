#include "mqtt_reference.h"

// Constructor to initialize the MQTT Client with parameters
//MQTTWrapper::MQTTWrapper(WiFiClientSecure& wifiClient)
MQTTWrapper::MQTTWrapper(WiFiClient& wifiClient)
  : mqttClient(wifiClient) {

  this->mqttBroker = "mqtt-staging.smartcitizen.me";
  this->mqttClientName = "Swarm_Reference";
  this->mqttUser = "fablabbcn102";
  this->mqttPass = "";
  this->topicsLength = 3;
  this->frequency = 0;

  // Correctly initialize the array of string literals
  this->topicsToPub[0] = "lab/swarm/cell1";
  this->topicsToPub[1] = "lab/swarm/cell2";
  this->topicsToPub[2] = "lab/swarm/cell3";
}

// Callback function for MQTT message handling
void MQTTWrapper::callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  frequency = 0;
  for (int i = 0; i < length; i++) {
    int digit = (char)payload[i] - '0';
    frequency = frequency * 10 + digit;
  }
  Serial.print("Frequency: ");
  Serial.print(frequency);
  tone(PinConfig::BUZZER, frequency, 500);
  Serial.println();
}

// Setup MQTT connection
void MQTTWrapper::setupMQTT() {
  mqttClient.setServer(this->mqttBroker, 1883);
  mqttClient.setCallback([this](char* topic, byte* payload, unsigned int length) { this->callback(topic, payload, length); });
  delay(1500);  // Allow the hardware to sort itself out
}

// MQTT connect function
void MQTTWrapper::mqttConnect() {
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (mqttClient.connect(mqttClientName, mqttUser, mqttPass)) {
      Serial.println("connected");
      // Subscribe to topicsToPub[1] = "lab/swarm/cell2"
      mqttClient.subscribe(topicsToPub[1]);
      Serial.print("subscribed to: ");
      Serial.println(topicsToPub[1]);
      // Publish to all topicsToPub
      for (int i = 0; i < topicsLength; i++) {
        mqttClient.publish(topicsToPub[i], "440");
        Serial.print("published to: ");
        Serial.println(topicsToPub[i]);
      }
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

// Send data to topics
void MQTTWrapper::sendData(char* data[]) {
  for (int i = 0; i < topicsLength; i++) {
    mqttClient.publish(topicsToPub[i], data[i]);
  }
}

// Loop function to check MQTT connection and sensor state
void MQTTWrapper::loopMQTT() {
  if (!mqttClient.connected()) {
    mqttConnect();
  }

  mqttClient.loop();
}
