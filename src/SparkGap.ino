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
  MOSFET mosfetA(12, "1");
  Relay relayA(12, "1");
  MOSFET mosfetB(13, "2");
  Relay relayB(13, "2");
  MOSFET mosfetC(5, "3");
  Relay relayC(5, "3");
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
    button.setCallback([] (int state) { if (state == PRESS) { relay.set(!relay.state); } });
  #endif

  #ifdef TYPE_MAGIC
    mosfetA.linkRelay(&relayA);
    mosfetB.linkRelay(&relayB);
    mosfetC.linkRelay(&relayC);
    button.setCallback([] (int state) {
      if (state == PRESS) {
        // If any relays are on, toggle to off, otherwise turn all on
        int newRelayState = (
          relayA.state == ON || 
          relayB.state == ON ||
          relayC.state == ON
          ) ? OFF : ON ;
        relayA.set(newRelayState);
        relayB.set(newRelayState);
        relayC.set(newRelayState);
      } 
    });
  #endif
}

void loop() {
  wps.loop();
  MQTT::instance.loop();
}
