#ifndef led_h
#define led_h

#include <Arduino.h>
#include "output.h"
#include "mqtt.h"
#define OFF 0
#define ON 1
#define WINK 2
#define BLINK 3
#define BLINK_FAST 4

#define LED_TOPIC "led"
#define LED_PIN 13

class LED: private Output {
  public:
    LED(int pin, char* suffix, MQTT *mqtt) : Output(pin, LED_TOPIC, suffix, mqtt) {};
    LED(char* suffix, MQTT *mqtt) : Output(LED_PIN, LED_TOPIC, suffix, mqtt) {};
    LED(int pin, MQTT *mqtt) : Output(pin, LED_TOPIC, mqtt) {};
    LED(MQTT *mqtt); // : Output(LED_PIN, LED_TOPIC, mqtt) {};
    void setup();
    void set(int state);
    void set(uint8_t* payload, char* topic);
    void get(char* topic);
    uint8_t status();
  private:
    // uint8_t pin;
    // MQTT& _mqtt;
    // char* topic;
    // char setTopic[50];
    // String getTopic;
    // String statusTopic;
    void handleMessage(char* topic, uint8_t* payload, unsigned int length);
    // virtual void subscribe();
};

#endif
