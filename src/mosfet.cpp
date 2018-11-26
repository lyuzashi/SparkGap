#include <Arduino.h>
#include <functional>
#include "stdlib_noniso.h"
#include "defines.h"
#include "mosfet.h"
#include "types.h"
#include "mqtt-smarthome.h"

void MOSFET::setup() {
  pinMode(pin, OUTPUT);
  analogWrite(pin, 0);
}

void MOSFET::set(int newState) {
  // TODO check valid state
  if(newState != state) {
    analogWrite(pin, newState);
    state = newState;
    stateChange();
  }
}

void MOSFET::set(uint8_t* payload, char* topic) {
  set(atoi((const char*)payload));
}

char* MOSFET::get(char* output) {
  return itoa(state, output, 10);
}
