#include "defines.h"
#include "mqtt.h"
#include "loop-queue.h"
#include <functional>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

WiFiClient espClient;

PubSubClient MQTT::client(espClient);

MQTT::MQTT() {
  client.setCallback([this] (char* topic, uint8_t* payload, unsigned int length) {
    this->callbackMessage(topic, payload, length); 
  });
  previousState = MQTT_DISCONNECTED;
  LoopQueue::onEveryLoop(std::bind(&MQTT::loop, this));
}

void MQTT::onMessage(std::function<void(char*, char*, unsigned int)> callback) {
  onMessageHandlers.push_back(callback);
}

void MQTT::callbackMessage(char* topic, uint8_t* payload, unsigned int length) {
  char buffer[length];
  strncpy(buffer, (const char*)payload, length);
  for(unsigned int i = 0; i < onMessageHandlers.size(); ++i) {
    onMessageHandlers[i](topic, buffer, length);
  }
}

boolean MQTT::loop() {
  if (previousState != client.state()) {
    int newState = client.state();
    previousState = newState;
    for(unsigned int i = 0; i < stateChange.size(); ++i) {
      std::function<void(int)> method = stateChange[i];
      LoopQueue::onLoop([newState, method] () { method(newState); } );
    }
  }
  return client.loop();
}

void MQTT::onStateChange(std::function<void(int)> callback) {
  stateChange.push_back(callback);
}
