#include "channel.h"
#include "setup.h"
#include "mqtt.h"
#include "defines.h"
#include "types.h"
#include "mqtt-smarthome.h"

Channel::Channel(int pin, char* topic, MQTT *mqtt) : Setup(), pin(pin), topic(topic), mqtt(mqtt) {
  init();
}


Channel::Channel(int pin, char* topic) : Setup(), pin(pin), topic(topic) {
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
    Serial.println(subscriptionTopics[i]);
    MQTT::client.subscribe(subscriptionTopics[i]);
  }
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

