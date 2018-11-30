#include <Arduino.h>
#include <FunctionalInterrupt.h>
#include <functional>
#include "stdlib_noniso.h"
#include "defines.h"
#include "motion.h"
#include "types.h"
#include "mqtt-smarthome.h"

void Motion::setup() {
  pinMode(pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(pin), std::bind(&Motion::changed, this), CHANGE);
}

char* Motion::get(char* output) {
  return itoa(state, output, 10);
}

void Motion::changed() {
  int newState = digitalRead();
  state = newState;
  stateChange();
}
