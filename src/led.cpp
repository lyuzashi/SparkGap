#include <Arduino.h>
#include "defines.h"
#include "led.h"
#include "mqtt.h"
#include "types.h"
#include "mqtt-smarthome.h"

// #define SET_TOPIC TOP_LEVEL "/" SET "/" NAME "/"

// void composeSetTopic(const char* topic, char* composite) {
//   char buffer[sizeof(SET_TOPIC) + sizeof(topic)];
//   strcpy(buffer, SET_TOPIC);
//   strcat(buffer, topic);
//   strcpy(composite, buffer);
  
// }

// LED::LED(int pin, MQTT *mqtt) : Output(pin, "led", mqtt) {

// }

// LED::LED(int pin, char* suffix, MQTT *mqtt) : Output(pin, "led", suffix, mqtt) {
  
  // composeSetTopic(topic, setTopic);
  // createGetTopic(getTopic, "on");

  // setTopic = String(TOP_LEVEL) + "/" + String(SET) + "/" + String(NAME) + "/" + topicName;
  // getTopic = String(TOP_LEVEL) + "/" + String(GET) + "/" + String(NAME) + "/" + topicName;
  // statusTopic = String(TOP_LEVEL) + "/" + String(STATUS) + "/" + String(NAME) + "/" + topicName;

  // mqtt->onMessage([this] (char* topic, uint8_t* payload, unsigned int length) { this->handleMessage(topic, payload, length); });

  // mqtt->onStateChange([this] (int mqttState) {
  //   if(mqttState == MQTT_CONNECTED) {
  //     this->subscribe();
  //   } 
  // });

  
// }

void LED::setup() {
  pinMode(pin, OUTPUT);
}

// Replaced with payload reading method
void LED::set(int state) {
  if (state == ON) {
    digitalWrite(pin, LOW);
  } else if (state == OFF) {
    digitalWrite(pin, HIGH);
  }
}

void LED::handleMessage(char* topic, uint8_t* payload, unsigned int length) {
  // This works, but moving setTopic to output
  // if (strncmp ((const char*)topic, setTopic, length) == 0) {
  //  if (strncmp ((const char*)payload, "1", length) == 0) {
  //   set(ON);
  //  }
  //  if (strncmp ((const char*)payload, "0", length) == 0) {
  //   set(OFF);
  //  }
  // }
}

// Moved to channel
// void LED::subscribe() {
//   mqtt->subscribe(setTopic);
// }

void LED::set(uint8_t* payload, char* topic) {
  // For PWM, can check topic for on/brightness
  set(atoi((const char*)payload));
}

void LED::get(char* topic) { }