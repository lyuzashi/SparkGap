#include "modules/led.h"
#include "modules/wps.h";

#include <ESP8266WiFi.h>

#define LED_TOPIC "led"

LED led(13, LED_TOPIC);

WPS wps;

void setup() {
  
  Serial.begin(115200);

}

void loop() {
  
  wps.loop();
  

  // led.set(ON);
  // delay(200);
  // led.set(OFF);
  // delay(200);

}
