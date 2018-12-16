#include "default.h"
#include "channel.h"
#include "mqtt.h"
#include "mqtt-smarthome.h"
#include "stdlib_noniso.h"
#include <EEPROM.h>

int Default::memoryLastIndex = 0;

Default::Default(char* topic, char* suffix) : Channel(-1, topic, suffix) {
  init();
}

Default::Default(char* suffix) : Channel(-1, DEFAULT_TOPIC, suffix) {
  init();
}


Default::Default() : Channel(-1, DEFAULT_TOPIC) {
  init();
}

void Default::init() {
  memoryIndex = memoryLastIndex;
  memoryLastIndex += sizeof(value);
  createTopic(setTopic, SET);
  subscriptionTopics.push_back(setTopic);
  MQTT::instance.onMessage([this] (char* topic, char* payload, unsigned int length) {
    if (strcmp (topic, this->setTopic) == 0) {
      set(payload, topic);
    };
  });
}

void Default::setup() {
  EEPROM.begin(memoryLastIndex);
  onChange(get());
}

void Default::set(char* payload, char* topic) {
  value = atoi(payload);
  wasUpdated = true;
  onChange(value);
  EEPROM.put(memoryIndex, value);
  EEPROM.commit();
}

int Default::get() {
  EEPROM.get(memoryIndex, value);
  return value;
}