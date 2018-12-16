#include "channel.h"
#include "setup.h"
#include "mqtt.h"
#include "defines.h"
#include "types.h"
#include "mqtt-smarthome.h"

Channel::Channel(int pin, char* topic) : Setup(), pin(pin), topic(topic) {
  init();
}

Channel::Channel(int pin, char* topic, bool invert) : Setup(), pin(pin), topic(topic), invert(invert) {
  init();
}

Channel::Channel(int pin, char* topic, char* suffix) : Setup(), pin(pin), topic(topic), suffix(suffix) {
  init();
}

Channel::Channel(int pin, char* topic, char* suffix, bool invert) : Setup(), pin(pin), topic(topic), suffix(suffix), invert(invert) {
  init();
}

void Channel::init() {
  MQTT::instance.onStateChange([this] (int mqttState) {
    if(mqttState == MQTT_CONNECTED) {
      this->subscribe();
    } 
  });
}

void Channel::subscribe() {
  for(unsigned int i = 0; i < subscriptionTopics.size(); ++i) {
    MQTT::client.subscribe(subscriptionTopics[i]);
  }
}

void Channel::createTopic(char* output, char* method) {
  bool hasSuffix = strcmp(suffix, "") != 0;
  strcpy(output, TOP_LEVEL);
  strcat(output, SP);
  strcat(output, method);
  strcat(output, SP);
  strcat(output, NAME);
  if (hasSuffix) {
    strcat(output, " ");
    strcat(output, suffix);
  }
  strcat(output, SP);
  strcat(output, topic);
}
