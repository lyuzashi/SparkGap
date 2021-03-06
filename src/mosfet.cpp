#include <Arduino.h>
#include <functional>
#include "stdlib_noniso.h"
#include "defines.h"
#include "mosfet.h"
#include "relay.h"
#include "types.h"
#include "mqtt-smarthome.h"
#include "default.h"

void MOSFET::setup() {
  pinMode(pin, OUTPUT);
  analogWrite(0);
  defaultBrightness.onChange = [this] (int value) {
    if (state == 0) {
      relayState = value;
    }
  };
}

void MOSFET::set(int newState) {
  int newStateLimited = std::min(PWMRANGE, std::max(0, newState));
  if(newStateLimited != state) {
    if (*switchState != NULL && *switchState == ON) {
      analogWrite(newStateLimited);
    }
    state = newStateLimited;
    stateChange();
    relayState = state == 0 ? defaultBrightness.get() : state;
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
  relay->level = &relayState;
}
