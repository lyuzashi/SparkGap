#include <Arduino.h>
#include <functional>
#include "stdlib_noniso.h"
#include "defines.h"
#include "mosfet.h"
#include "types.h"
#include "mqtt-smarthome.h"

void MOSFET::setup() {
  pinMode(pin, OUTPUT);
  analogWrite(0);
}

void MOSFET::set(int newState) {
  // TODO check valid state
  if(newState != state) {
    analogWrite(newState);
    state = newState;
    Serial.println(newState);
    Serial.println(state);
    stateChange();
  }
}

void MOSFET::set(char* payload, char* topic) {
  Serial.print("New MOSFET state");
  Serial.println(payload);
  set(atoi(payload));
}

char* MOSFET::get(char* output) {
  return itoa(state, output, 10);
}
