#include <Arduino.h>
#include "defines.h"
#include "led.h"
#include "mqtt.h"
#include "types.h"
#include "mqtt-smarthome.h"

LED::LED(int pinNumber, const char* topicName, MQTT *mqtt) {
  pinMode(pinNumber, OUTPUT);
  pin = pinNumber;
  topic = topicName;
  setTopic = String(TOP_LEVEL) + "/" + String(SET) + "/" + String(NAME) + "/" + topicName;
  getTopic = String(TOP_LEVEL) + "/" + String(GET) + "/" + String(NAME) + "/" + topicName;
  statusTopic = String(TOP_LEVEL) + "/" + String(STATUS) + "/" + String(NAME) + "/" + topicName;

  mqtt->onMessage([this] (char* topic, uint8_t* payload, unsigned int length) { this->handleMessage(topic, payload, length); });

}

void LED::set(int state) {
  if (state == ON) {
    digitalWrite(pin, LOW);
  } else if (state == OFF) {
    digitalWrite(pin, HIGH);
  }
}

void LED::handleMessage(char* topic, uint8_t* payload, unsigned int length) {
   if (strncmp ((const char*)payload, "1", length) == 0) {
    set(ON);
   }
   if (strncmp ((const char*)payload, "0", length) == 0) {
    set(OFF);
   }
}
