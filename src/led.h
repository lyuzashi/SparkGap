#ifndef led_h
#define led_h

#include <Arduino.h>
#include "Ticker.h"
#include "output.h"
#define OFF 0
#define ON 1
#define WINK 2
#define BLINK 3
#define BLINK_FAST 4

#define LED_TOPIC "led"
#define LED_PIN 13

class LED: private Output {
  public:
    LED(int pin, char* suffix) : Output(pin, LED_TOPIC, suffix) {};
    LED(char* suffix) : Output(LED_PIN, LED_TOPIC, suffix) {};
    LED(int pin) : Output(pin, LED_TOPIC) {};
    LED() : Output(LED_PIN, LED_TOPIC) {};
    void setup();
    void set(int state);
    void set(char* payload, char* topic);
    char* get(char* output);
  private:
    int state;
    Ticker interval;
    void blink();
    void wink(int previousState);
};

#endif
