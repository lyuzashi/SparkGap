#include <Arduino.h>
#include "stdlib_noniso.h"
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
    state = newState;
    Input::stateChange();
  }
}

void LED::set(uint8_t* payload, char* topic) {
  // For PWM, can check topic for on/brightness
  set(atoi((const char*)payload));
}

char* LED::get(char* output) {
  return itoa(state, output, 10);
}
