#include <Arduino.h>
#include "defines.h"
#include "led.h"
#include "types.h"
#include "mqtt-smarthome.h"

LED::LED(int pinNumber, const char* topicName) {
  pinMode(pinNumber, OUTPUT);
  pin = pinNumber;
  topic = topicName;
  setTopic = String(TOP_LEVEL) + "/" + String(SET) + "/" + String(NAME) + "/" + topicName;
  getTopic = String(TOP_LEVEL) + "/" + String(GET) + "/" + String(NAME) + "/" + topicName;
  statusTopic = String(TOP_LEVEL) + "/" + String(STATUS) + "/" + String(NAME) + "/" + topicName;
}

void LED::set(int state) {
  if (state == ON) {
    digitalWrite(pin, LOW);
  } else if (state == OFF) {
    digitalWrite(pin, HIGH);
  }
}
