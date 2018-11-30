#include "output.h"
#include "input.h"
#include "mqtt.h"
#include "mqtt-smarthome.h"

Output::Output(int pin, char* topic, char* suffix, bool invert) : invert(invert), Input(pin, topic, suffix) {
  init();
};

Output::Output(int pin, char* topic, char* suffix) : Input(pin, topic, suffix) {
  init();
};

Output::Output(int pin, char* topic, bool invert) : invert(invert), Input(pin, topic) {
  init();
};

Output::Output(int pin, char* topic) : Input(pin, topic) {
  init();
};

void Output::init() {

  createTopic(setTopic, SET);

  subscriptionTopics.push_back(setTopic);

  MQTT::instance.onMessage([this] (char* topic, char* payload, unsigned int length) {
    if (strcmp (topic, this->setTopic) == 0) {
      set(payload, topic);
    };
  });
};

