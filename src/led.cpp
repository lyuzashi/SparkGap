#include <Arduino.h>
#include "Ticker.h"
#include <functional>
#include "stdlib_noniso.h"
#include "defines.h"
#include "led.h"
#include "types.h"
#include "mqtt-smarthome.h"

void LED::setup() {
  pinMode(pin, OUTPUT);
  digitalWrite(LOW);
}

void LED::set(int newState) {
  // TODO check valid state
  if(newState != state) {
    // Detatch any timers if set
    interval.detach();
    if (newState == ON) {
      digitalWrite(HIGH);
    } else if (newState == OFF) {
      digitalWrite(LOW);
    }
    if (newState == BLINK) {
      interval.attach(0.3, std::bind(&LED::blink, this));
    }
    if (newState == BLINK_FAST) {
      interval.attach(0.1, std::bind(&LED::blink, this));
    }
    if (newState == WINK) {
      digitalWrite(LOW);
      interval.attach(0.2, std::bind(&LED::wink, this, state));
    }
    state = newState;
    stateChange();
  }
}

void LED::set(char* payload, char* topic) {
  // For PWM, can check topic for on/brightness
  set(atoi(payload));
}

char* LED::get(char* output) {
  return itoa(state, output, 10);
}

void LED::blink() {
  if (state == BLINK || state == BLINK_FAST) {
    int blinkState = digitalRead(pin);
    digitalWrite(!blinkState);
  }
}

void LED::wink(int previousState) {
  if (state == WINK) {
    // TODO digitalRead needs implimenting with invert support
    int blinkState = digitalRead(pin);
    digitalWrite(!blinkState);
    if (blinkState == LOW) {
      set(previousState);
    }
  }
}
