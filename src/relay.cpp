#include <Arduino.h>
#include <functional>
#include "stdlib_noniso.h"
#include "defines.h"
#include "relay.h"
#include "types.h"
#include "mqtt-smarthome.h"

void Relay::setup() {
  pinMode(pin, OUTPUT);
  digitalWrite(LOW);
}

void Relay::set(int newState) {
  // TODO check valid state
  if(newState != state) {
    Serial.print("New Relay state");
    Serial.println(newState);
    if (newState == ON) {
      if (level == NULL) {
        digitalWrite(LOW);
      } else {
        analogWrite(*level);
      }
    } else if (newState == OFF) {
      digitalWrite(HIGH);
    }
    state = newState;
    stateChange();
  }
}

void Relay::set(char* payload, char* topic) {
  // For PWM, can check topic for on/brightness
  set(atoi(payload));
}

char* Relay::get(char* output) {
  return itoa(state, output, 10);
}
