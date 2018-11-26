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

Input::Input(int pin, char* topic) : Channel(pin, topic) {
  init();
};

void Input::init() {
  createTopic(getTopic, GET);
  createTopic(statusTopic, STATUS);

  subscriptionTopics.push_back(getTopic);

  // Register a new callback for MQTT messages, specific to this topic
  MQTT::instance.onMessage([this] (char* topic, uint8_t* payload, unsigned int length) {
    if (strcmp (topic, this->getTopic) == 0) {
      stateChange();
    };
  });
};

void Input::stateChange() {
  // How to execute this method in multi-inheritance?
  // TODO only publish when clinet connected 
  char buffer[16];
  MQTT::client.publish(statusTopic, get(buffer));
};

