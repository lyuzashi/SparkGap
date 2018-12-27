#include <Arduino.h>
#include <vector>
#include "defines.h"
#include "types.h"
#include "setup.h"
#include "led.h"
#include "relay.h"
#include "button.h"
#include "mosfet.h"
#include "motion.h"
#include "wps.h"
#include "dnssd.h"
#include "mqtt.h"
#include "loop-queue.h"

WPS wps;
DNSSD dnssd;
MQTT MQTT::instance;

#ifdef TYPE_BASIC
  LED led;
  Relay relay;
  Button button;
#endif

#ifdef TYPE_FOUR
  LED led;
  Relay relay1("1");
  Relay relay2(5, "2");
  Relay relay3(4, "3");
  Relay relay4(15, "4");
  Button button1("1");
  Button button2(9, "2");
  Button button3(10, "3");
  Button button4(14, "4");
#endif

#ifdef TYPE_MAGIC
  LED led(15);
  MOSFET mosfetA(12, "1");
  Relay relayA(12, "1");
  MOSFET mosfetB(13, "2");
  Relay relayB(13, "2");
  MOSFET mosfetC(5, "3");
  Relay relayC(5, "3");
  Button button;
  Motion motion;
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
    LoopQueue::onLoop([] () { dnssd.find(); }, 1500);
  }
  if (state == DNSSD_NOT_FOUND) {
    dnssd.forget();
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
  if (state == MQTT_CONNECTION_TIMEOUT || state == MQTT_CONNECTION_LOST || state == MQTT_CONNECT_FAILED || state == MQTT_DISCONNECTED) {
    MQTT::client.disconnect();
    dnssd.forget();
  }
  if (state == MQTT_CONNECTED) {
    led.set(OFF);
    led.set(WINK);
  }
}

void setup() {
  Serial.begin(115200);
  wps.setCallback(wpsState);
  dnssd.setCallback(dnssdState);
  MQTT::instance.onStateChange(mqttState);

  Setup::run();

  #ifdef TYPE_BASIC
    button.setCallback([] (int state) {
      if (state == PRESS) { relay.set(!relay.state); } 
      if (state == LONG_PRESS) { wps.reset(); }
    });
  #endif

  #ifdef TYPE_FOUR
    button1.setCallback([] (int state) { if (state == PRESS) { relay1.set(!relay1.state); } });
    button2.setCallback([] (int state) { if (state == PRESS) { relay2.set(!relay2.state); } });
    button3.setCallback([] (int state) { if (state == PRESS) { relay3.set(!relay3.state); } });
    button4.setCallback([] (int state) { if (state == PRESS) { relay4.set(!relay4.state); } });
  #endif

  #ifdef TYPE_MAGIC
    led.invert = false;
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
  LoopQueue::loop();
}
