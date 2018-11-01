#include <Arduino.h>
#include "led.h"

void LED(int state) {
  if (state == ON) {
    digitalWrite(13, HIGH);
  }
}