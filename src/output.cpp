#include "output.h"
#include "input.h"
#include "mqtt.h"
#include "mqtt-smarthome.h"

Output::Output(int pin, char* topic, char* suffix, MQTT *mqtt) : Input(pin, topic, suffix, mqtt) {
  init();
};

Output::Output(int pin, char* topic, MQTT *mqtt) : Input(pin, topic, mqtt) {
  init();
};

void Output::init() {

  createTopic(setTopic, SET);

  subscriptionTopics.push_back(setTopic);

  mqtt->onMessage([this] (char* topic, uint8_t* payload, unsigned int length) {
    if (strcmp (topic, this->setTopic) == 0) {
      set(payload, topic);
    };
  });
};

