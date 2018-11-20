#include <Arduino.h>
#include "defines.h"
#include "led.h"
#include "mqtt.h"
#include "types.h"
#include "mqtt-smarthome.h"


LED::LED(MQTT *mqtt) : Output(LED_PIN, LED_TOPIC, mqtt) {
  setup();
};


void LED::setup() {
  pinMode(pin, OUTPUT);
}

void LED::set(int state) {
  if (state == ON) {
    digitalWrite(pin, LOW);
  } else if (state == OFF) {
    digitalWrite(pin, HIGH);
  }
}

void LED::set(uint8_t* payload, char* topic) {
  // For PWM, can check topic for on/brightness
  set(atoi((const char*)payload));
}

void LED::get(char* topic) { }