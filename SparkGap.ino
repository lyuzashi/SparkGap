#include "modules/led.h"

#define LED_TOPIC "led"

LED led(13, LED_TOPIC);

void setup() {
}

void loop() {
  led.set(ON);
  delay(200);
  led.set(OFF);
  delay(200);
}
