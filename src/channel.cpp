#include "channel.h"
#include "mqtt.h"
#include "defines.h"
#include "types.h"
#include "mqtt-smarthome.h"

Channel::Channel(int pin, char* topic, MQTT *mqtt) : pin(pin), topic(topic), mqtt(mqtt) {
  // Call subscribe setup here

  // Input/output channels create their own topics, subscribe and register onMessage
  // listeners that ensure their topic matches and eventually calls a callback for get or set
  // These can be scoped to multiple inheritance with virtual inheritace to manage the
  // individual callbacks
  // https://stackoverflow.com/a/23231363/2530832

  mqtt->onMessage([this] (char* topic, uint8_t* payload, unsigned int length) {
    this->handleMessage(topic, payload, length);
  });

  mqtt->onStateChange([this] (int mqttState) {
    if(mqttState == MQTT_CONNECTED) {
      this->subscribe();
    } 
  });

}

void Channel::createTopic(char* output, char* method) {
  char buffer[sizeof(TOP_LEVEL) + 1 + sizeof(method) + 1 + sizeof(NAME) + 1 + sizeof(topic)];
  strcpy(buffer, TOP_LEVEL);
  strcat(buffer, SP);
  strcat(buffer, method);
  strcat(buffer, SP);
  strcat(buffer, NAME);
  strcat(buffer, SP);
  strcat(buffer, topic);
  strcat(output, buffer);
}

void Channel::createTopic(char* output, char* method, char* suffix) {
  char buffer[sizeof(TOP_LEVEL) + 1 + sizeof(method) + 1 + sizeof(NAME) + 1 + sizeof(suffix) + 1 + sizeof(topic)];
  strcpy(buffer, TOP_LEVEL);
  strcat(buffer, SP);
  strcat(buffer, method);
  strcat(buffer, SP);
  strcat(buffer, NAME);
  strcat(buffer, " ");
  strcat(buffer, suffix);
  strcat(buffer, SP);
  strcat(buffer, topic);
  strcat(output, buffer);
}
