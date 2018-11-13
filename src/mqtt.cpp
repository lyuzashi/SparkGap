#include "defines.h"
#include "mqtt.h"
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

WiFiClient espClient;
PubSubClient _client(espClient);

MQTT::MQTT() {
  client = &_client;
  client->setCallback([this] (char* topic, uint8_t* payload, unsigned int length) { this->callbackMessage(topic, payload, length); });
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
  if (previousState != client->state()) {
    previousState = client->state();
    for(unsigned int i = 0; i < stateChange.size(); ++i) {
      stateChange[i](previousState);
    }
  }
  return client->loop();
}

void MQTT::onStateChange(void (*callback)(int)) {
  stateChange.push_back(callback);
}

void MQTT::setServer(IPAddress ip, uint16_t port) {
  client->setServer(ip, port);
}

boolean MQTT::subscribe(const char* topic) {
  return client->subscribe(topic);
}

boolean MQTT::connect(const char* id) {
  return client->connect(id);
}