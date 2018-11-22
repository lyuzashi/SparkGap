#include "input.h"
#include "channel.h"
#include "mqtt.h"
#include "mqtt-smarthome.h"

Input::Input(int pin, char* topic, char* suffix, MQTT *mqtt) : Channel(pin, topic, suffix, mqtt) {
  init();
};

Input::Input(int pin, char* topic, MQTT *mqtt) : Channel(pin, topic, mqtt) {
  init();
};

void Input::init() {
  createTopic(getTopic, GET);
  createTopic(statusTopic, STATUS);

  subscriptionTopics.push_back(getTopic);

  // Register a new callback for MQTT messages, specific to this topic
  mqtt->onMessage([this] (char* topic, uint8_t* payload, unsigned int length) {
    if (strcmp (topic, this->getTopic) == 0) {
      MQTT::client.publish(statusTopic, get(topic));
    };
  });
};

void Input::stateChange(char* state, char* topic) {
 // How to execute this method in multi-inheritance?
};

