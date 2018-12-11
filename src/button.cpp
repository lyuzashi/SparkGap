#include <Arduino.h>
#include <FunctionalInterrupt.h>
#include <functional>
#include "stdlib_noniso.h"
#include "defines.h"
#include "button.h"
#include "types.h"
#include "mqtt-smarthome.h"
#include "loop-queue.h";

void Button::setup() {
  pinMode(pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pin), std::bind(&Button::changed, this), CHANGE);
  LoopQueue::onEveryLoop(std::bind(&Button::checkLongPress, this));
}

char* Button::get(char* output) {
  return itoa(state, output, 10);
}

bool Button::debounce() {
  // Returns true if was not bouncing
  if (bouncing == false) {
    bouncing = true;
    LoopQueue::onLoop([this] () {
      bouncing = false;
      if (rawState == LOW && state != IDLE) {
        stateChange(IDLE);
      }
    }, DEBOUNCE_DELTA);
    return true;
  }
  return false;
}

void Button::checkLongPress() {
  if (longPressing == true && (millis() - riseTime) >= LONG_DELTA) {
    longPressing = false;
    state = LONG_PRESS;
    debounce();
    stateChange();
  }
}

void Button::changed() {
  rawState = digitalRead();
  if (debounce() == false) { return; }
  if (rawState == HIGH) {
    riseTime = millis();
    longPressing = true;
  } else if (rawState == LOW) {
    longPressing = false;
    if ((millis() - riseTime) < LONG_DELTA) {
      state = PRESS;
      stateChange();
    }
  }
}