#include <Arduino.h>
#include <FunctionalInterrupt.h>
#include <functional>
#include "stdlib_noniso.h"
#include "defines.h"
#include "button.h"
#include "types.h"
#include "mqtt-smarthome.h"

void Button::setup() {
  pinMode(pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(pin), std::bind(&Button::changed, this), CHANGE);
}

char* Button::get(char* output) {
  return itoa(state, output, 10);
}

void Button::changed() {
  int newState = digitalRead();
  if (newState == LOW) {
    // Rising edge
    // Store time
    riseTime = millis();
  } else if (newState == HIGH) {
    if (millis() - riseTime < DEBOUNCE_DELTA) {
      return;
    }
    if (millis() - riseTime < LONG_DELTA) {
      state = PRESS;
      stateChange();
      return;
    }
    state = LONG_PRESS;
    stateChange();
  }
}