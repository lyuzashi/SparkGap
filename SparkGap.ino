#include "modules/led.h"
#include "modules/wps.h";
#include "modules/dnssd.h";

#define LED_TOPIC "led"

WPS wps;
DNSSD dnssd("mqtt", "tcp");
LED led(13, LED_TOPIC);


void wpsState(int state) {
  Serial.printf("State %d\n", state);
  if (state == WPS_CONNECTED) {
    led.set(OFF);
    dnssd.setup();
  }
}

void dnssdState(int state) {
  Serial.printf("MDNS state %d\n", state);
  if (state == DNSSD_IDLE) {
    dnssd.find();
  }
  if (state == DNSSD_NOT_FOUND) {
    dnssd.find();
  }
  if (state == DNSSD_FAILED) {
    // Gets in a loop if this is attempted again :(
  }
  if (state == DNSSD_FOUND) {
    Serial.printf("MDNS found port %d\n", dnssd.port);
    Serial.print(dnssd.ip);
  }
}

void setup() {
  
  Serial.begin(115200);
  Serial.printf("Chip ID %d", ESP.getChipId());
  wps.setCallback(wpsState);
  dnssd.setCallback(dnssdState);

}

void loop() {
  
  wps.loop();
  

  // led.set(ON);
  // delay(200);
  // led.set(OFF);
  // delay(200);

}
