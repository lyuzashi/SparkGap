#include "output.h"
#include "input.h"
#include "mqtt.h"
#include "mqtt-smarthome.h"

Output::Output(int pin, char* topic, char* suffix, MQTT *mqtt) : Input(pin, topic, suffix, mqtt) {
  Output::setup();
};

Output::Output(int pin, char* topic, MQTT *mqtt) : Input(pin, topic, mqtt) {
  Output::setup();
};

void Output::setup() {

  createTopic(setTopic, SET);

  subscriptionTopics.push_back(setTopic);

  mqtt->onMessage([this] (char* topic, uint8_t* payload, unsigned int length) {
    if (strncmp ((const char*)topic, setTopic, sizeof(topic)) == 0) {
      set(payload, topic);
    };
  });
};

