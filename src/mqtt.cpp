#include "defines.h"
#include "mqtt.h"
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

MQTT::MQTT(): PubSubClient() {
  WiFiClient espClient;
  setClient(espClient);
  setCallback([this] (char* topic, uint8_t* payload, unsigned int length) { this->callbackMessage(topic, payload, length); });
  previousState = MQTT_DISCONNECTED;
}

void MQTT::onMessage(void (*callback)(char*, uint8_t*, unsigned int)) {
  onMessageHandlers.push_back(callback);
}

void MQTT::callbackMessage(char* topic, uint8_t* payload, unsigned int length) {
  for(unsigned int i = 0; i < onMessageHandlers.size(); ++i) {
    onMessageHandlers[i](topic, payload, length);
  }
}

boolean MQTT::loop() {
  if (previousState != state()) {
    previousState = state();
    for(unsigned int i = 0; i < stateChange.size(); ++i) {
      stateChange[i](state());
    }
  }
  return PubSubClient::loop();
}

void MQTT::onStateChange(void (*callback)(int)) {
  stateChange.push_back(callback);
}
