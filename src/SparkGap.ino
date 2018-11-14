#include <Arduino.h>
#include <vector>
#include "defines.h"
#include "led.h"
#include "wps.h"
#include "dnssd.h"
#include "mqtt.h"

WPS wps;
DNSSD dnssd("mqtt", "tcp");
MQTT mqtt;
LED led(13, LED_TOPIC, &mqtt);

void wpsState(int state) {
  Serial.printf("State %d\n", state);
  if (state == WPS_CONNECTED) {
    led.set(OFF);
    Serial.println("Connected to WIFI, about to start discovery");
    dnssd.setup();
  }
}

void printMessage(char* topic, uint8_t* payload, unsigned int length) {
  Serial.print(topic);
  Serial.print(" : ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.print("\n");
}

void printMessage2(char* topic, uint8_t* payload, unsigned int length) {
  Serial.print(topic);
  Serial.print(" :2 ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.print("\n");
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
    mqtt.setServer(dnssd.ip, dnssd.port);
    if (mqtt.connect(NAME)) {
      Serial.println("connected");
      // client.publish("outTopic", "hello world");
      mqtt.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      // Serial.print(client.state());
    }
    
  }
}


void setup() {
  
  Serial.begin(115200);
  Serial.printf("Chip ID %d", ESP.getChipId());
  wps.setCallback(wpsState);
  dnssd.setCallback(dnssdState);
  mqtt.onMessage(printMessage);
  mqtt.onMessage(printMessage2);
}

void loop() {
  
  wps.loop();
  mqtt.loop();

  // led.set(ON);
  // delay(200);
  // led.set(OFF);
  // delay(200);

}
