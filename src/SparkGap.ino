#include <Arduino.h>
#include <vector>
#include "defines.h"
#include "types.h"
#include "setup.h"
#include "led.h"
#include "relay.h"
#include "button.h"
#include "mosfet.h"
#include "wps.h"
#include "dnssd.h"
#include "mqtt.h"

WPS wps;
DNSSD dnssd;
MQTT MQTT::instance;

#ifdef TYPE_BASIC
  LED led;
  Relay relay;
  Button button;
#endif

#ifdef TYPE_MAGIC
  MOSFET mosfet(13);
  Relay relay(13);
  Button button;
#endif


void wpsState(int state) {
  if (state == WPS_CONNECTED) {
    dnssd.setup();
  } else {
    led.set(BLINK);
  }
}

void dnssdState(int state) {
  if (state == DNSSD_IDLE) {
    dnssd.find();
  }
  if (state == DNSSD_NOT_FOUND) {
    dnssd.find();
  }
  if (state == DNSSD_FAILED) {
    dnssd.forget();
  }
  if (state == DNSSD_FOUND) {
    MQTT::client.setServer(dnssd.ip, dnssd.port);
    MQTT::client.connect(NAME, NAME, String(ESP.getChipId()).c_str());
  } else {
    led.set(BLINK_FAST);
  }
}

void buttonState(int state) {
  if (state == LONG_PRESS) {
    led.set(BLINK_FAST);
    wps.reset();
  }
}

void mqttState(int state) {
  if (state == MQTT_CONNECTION_LOST || state == MQTT_CONNECT_FAILED || state == MQTT_DISCONNECTED) {
    dnssd.forget();
  }
  if (state == MQTT_CONNECTED) {
    led.set(OFF);
    led.set(WINK);
  }
}

void setup() {
  Serial.begin(115200);
  Setup::run();

  wps.setCallback(wpsState);
  dnssd.setCallback(dnssdState);

  MQTT::instance.onStateChange(mqttState);

  #ifdef TYPE_BASIC
    button.setCallback(buttonState);
  #endif

  #ifdef TYPE_MAGIC
    mosfet.linkRelay(&relay);
  #endif
}

void loop() {
  wps.loop();
  MQTT::instance.loop();
}
