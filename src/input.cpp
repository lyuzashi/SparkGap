#include "Arduino.h"
#include "input.h"
#include "channel.h"
#include "mqtt.h"
#include "mqtt-smarthome.h"

Input::Input(int pin, char* topic, char* suffix) : Channel(pin, topic, suffix) {
  init();
};

Input::Input(int pin, char* topic, char* suffix, bool invert) : Channel(pin, topic, suffix, invert) {
  init();
};

Input::Input(int pin, char* topic) : Channel(pin, topic) {
  init();
};

Input::Input(int pin, char* topic, bool invert) : Channel(pin, topic, invert) {
  init();
};

void Input::init() {
  createTopic(getTopic, GET);
  createTopic(statusTopic, STATUS);

  subscriptionTopics.push_back(getTopic);

  // Register a new callback for MQTT messages, specific to this topic
  MQTT::instance.onMessage([this] (char* topic, char* payload, unsigned int length) {
    if (strcmp (topic, this->getTopic) == 0) {
      stateChange();
    };
  });
};

void Input::stateChange() {
  // How to execute this method in multi-inheritance?
  // TODO only publish when clinet connected 
  char buffer[16];
  Serial.println(getTopic);
  Serial.println(statusTopic);
  MQTT::client.publish(statusTopic, get(buffer));
};

int Input::digitalRead() {
  return invert ? !::digitalRead(pin) : ::digitalRead(pin);
};
