#include "defines.h"
#include "mqtt.h"
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

WiFiClient espClient;

PubSubClient MQTT::client(espClient);

MQTT::MQTT() {
  client.setCallback([this] (char* topic, uint8_t* payload, unsigned int length) {
    this->callbackMessage(topic, payload, length); 
  });
  previousState = MQTT_DISCONNECTED;
}

void MQTT::onMessage(std::function<void(char*, uint8_t*, unsigned int)> callback) {
  onMessageHandlers.push_back(callback);
}

void MQTT::callbackMessage(char* topic, uint8_t* payload, unsigned int length) {
  for(unsigned int i = 0; i < onMessageHandlers.size(); ++i) {
    onMessageHandlers[i](topic, payload, length);
  }
}

boolean MQTT::loop() {
  if (previousState != client.state()) {
    previousState = client.state();
    for(unsigned int i = 0; i < stateChange.size(); ++i) {
      Serial.printf("sending state %d to cb %d\n", previousState, i);
      stateChange[i](previousState);
    }
  }
  return client.loop();
}

void MQTT::onStateChange(std::function<void(int)> callback) {
  stateChange.push_back(callback);
}
