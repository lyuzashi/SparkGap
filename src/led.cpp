#include <Arduino.h>
#include "defines.h"
#include "led.h"
#include "mqtt.h"
#include "types.h"
#include "mqtt-smarthome.h"

void LED::setup() {
  pinMode(pin, OUTPUT);
}

void LED::set(int newState) {
  if (newState == ON) {
    digitalWrite(pin, LOW);
  } else if (newState == OFF) {
    digitalWrite(pin, HIGH);
  }
  if(newState != state) {
    Output::stateChange();
  }
  state = newState;
}

void LED::set(uint8_t* payload, char* topic) {
  // For PWM, can check topic for on/brightness
  set(atoi((const char*)payload));
}

char* LED::get(char* topic) {
  // For PWM, can check topic for on/brightness
  char buffer[16];
  return itoa(state, buffer, 10);
}
