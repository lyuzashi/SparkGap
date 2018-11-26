#include <Arduino.h>
#include <functional>
#include "stdlib_noniso.h"
#include "defines.h"
#include "relay.h"
#include "types.h"
#include "mqtt-smarthome.h"

void Relay::setup() {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}

void Relay::set(int newState) {
  // TODO check valid state
  if(newState != state) {
    if (newState == ON) {
      if (level == NULL) {
        digitalWrite(pin, HIGH);
      } else {
        analogWrite(pin, (int)level);
      }
    } else if (newState == OFF) {
      digitalWrite(pin, LOW);
    }
    state = newState;
    stateChange();
  }
}

void Relay::set(uint8_t* payload, char* topic) {
  // For PWM, can check topic for on/brightness
  set(atoi((const char*)payload));
}

char* Relay::get(char* output) {
  return itoa(state, output, 10);
}
