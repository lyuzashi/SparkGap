#include "Arduino.h"
#include "output.h"
#include "input.h"
#include "mqtt.h"
#include "mqtt-smarthome.h"

Output::Output(int pin, char* topic, char* suffix, bool invert) : Input(pin, topic, suffix, invert) {
  init();
};

Output::Output(int pin, char* topic, char* suffix) : Input(pin, topic, suffix) {
  init();
};

Output::Output(int pin, char* topic, bool invert) : Input(pin, topic, invert) {
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

void Output::digitalWrite(uint8_t value) {
  ::digitalWrite(pin, invert ? !value : value);
}

void Output::analogWrite(int value) {
  ::analogWrite(pin, invert ? PWMRANGE - value : value);
}
