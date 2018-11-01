#include "modules/led.h"

#define LED_TOPIC "led"

LED led(13, LED_TOPIC);

void setup() {
}

void loop() {
  led.state(ON);
}