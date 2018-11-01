#include <Arduino.h>
#include "led.h"
#include "types.h"
#include "mqtt-smarthome.h"

LED::LED(int pinNumber, const char* topicName) {
  pinMode(pinNumber, OUTPUT);
  pin = pinNumber;
  topic = topicName;
  // TODO join with "/"
  setTopic = strcat(strcat(strcat(TOP_LEVEL, SET), NAME), topicName);
  getTopic = strcat(strcat(strcat(TOP_LEVEL, GET), NAME), topicName);
  statusTopic = strcat(strcat(strcat(TOP_LEVEL, STATUS), NAME), topicName);
}

void LED::state(int state) {
  if (state == ON) {
    digitalWrite(13, HIGH);
  } else if (state == OFF) {
    digitalWrite(13, LOW);
  }
}