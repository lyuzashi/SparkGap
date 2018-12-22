#include "Arduino.h"
#include "output.h"
#include "input.h"
#include "mqtt.h"
#include "mqtt-smarthome.h"
#include "loop-queue.h"

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

  // Update ≈ 24fps
  LoopQueue::onEveryLoop(std::bind(&Output::update, this), 40);
  transitioningState = state;
};

void Output::digitalWrite(uint8_t value) {
  ::digitalWrite(pin, invert ? !value : value);
}

// void Output::analogWrite(int value) {
//   ::analogWrite(pin, invert ? PWMRANGE - value : value);
// }

float linear(float t) {
  return t;
}
float easeInQuad(float t) {
  return t * t;
}
float easeOutQuad(float t) {
  return t * (2 - t);
}
float easeInOutQuad(float t) {
  return t < 0.5 ? 2 * t * t : -1 + (4 - 2 * t) * t;
}

void Output::analogWrite(int value) {
  start = (float)transitioningState;
  destination = (float)value;
  startTime = (float)millis();
  isTransitionining = true;
}

void Output::update() {
  if (isTransitionining) {
    float now = (float)millis();
    float time = std::min((float)1, ((now - startTime) / transitionTime));
    float timeFunction = easeOutQuad(time);
    float val = ceil((timeFunction * (destination - start)) + start);
    transitioningState = (int)val;
    ::analogWrite(pin, invert ? PWMRANGE - transitioningState : transitioningState);
    isTransitionining = val != destination;
  }
}
