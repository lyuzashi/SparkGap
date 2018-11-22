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
  state = newState;
  if (state == ON) {
    digitalWrite(pin, LOW);
  } else if (state == OFF) {
    digitalWrite(pin, HIGH);
  }
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
