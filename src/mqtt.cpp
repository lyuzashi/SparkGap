#include "defines.h"
#include "mqtt.h"
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

MQTT::MQTT(WiFiClient client): PubSubClient() {
  setClient(client);
  setCallback([this] (char* topic, uint8_t* payload, unsigned int length) { this->callbackMessage(topic, payload, length); });

  // Is it possible to overload the _state= method?
}

void MQTT::onMessage(void (*callback)(char*, uint8_t*, unsigned int)) {
  onMessageHandlers.push_back(callback);
}

void MQTT::callbackMessage(char* topic, uint8_t* payload, unsigned int length) {
  for(unsigned int i = 0; i < onMessageHandlers.size(); ++i) {
    onMessageHandlers[i](topic, payload, length);
  }
}
