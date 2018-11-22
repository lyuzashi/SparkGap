#include <Arduino.h>
#include <vector>
#include "defines.h"
#include "setup.h"
#include "led.h"
#include "wps.h"
#include "dnssd.h"
#include "mqtt.h"

WPS wps;
DNSSD dnssd("mqtt", "tcp");
MQTT mqtt;
LED led(&mqtt);

void wpsState(int state) {
  Serial.printf("State %d\n", state);
  if (state == WPS_CONNECTED) {
    led.set(OFF);
    Serial.println("Connected to WIFI, about to start discovery");
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
    MQTT::client.setServer(dnssd.ip, dnssd.port);
    if (MQTT::client.connect(NAME, NAME, String(ESP.getChipId()).c_str())) {
      Serial.println("connected");
      // client.publish("outTopic", "hello world");
      MQTT::client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      // Serial.print(client.state());
    }
    
  }
}


void setup() {
  Setup::run();
  Serial.begin(115200);
  Serial.printf("Chip ID %d", ESP.getChipId());
  wps.setCallback(wpsState);
  dnssd.setCallback(dnssdState);
}

void loop() {
  
  wps.loop();
  mqtt.loop();

  // led.set(ON);
  // delay(200);
  // led.set(OFF);
  // delay(200);

}
