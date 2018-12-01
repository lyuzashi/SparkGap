#include <Arduino.h>
#include <functional>
#include "stdlib_noniso.h"
#include "defines.h"
#include "mosfet.h"
#include "relay.h"
#include "types.h"
#include "mqtt-smarthome.h"

void MOSFET::setup() {
  pinMode(pin, OUTPUT);
  analogWrite(0);
}

void MOSFET::set(int newState) {
  // TODO check valid state
  if(newState != state) {
    if (*switchState != NULL && *switchState == ON) {
      analogWrite(newState);
    }
    state = newState;
    stateChange();
  }
}

void MOSFET::set(char* payload, char* topic) {
  set(atoi(payload));
}

char* MOSFET::get(char* output) {
  return itoa(state, output, 10);
}

void MOSFET::linkRelay(Relay* relay) {
  switchState = &relay->state;
  relay->level = &state;
}