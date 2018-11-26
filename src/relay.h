#ifndef relay_h
#define relay_h

#include <Arduino.h>
#include "output.h"
#define OFF 0
#define ON 1

#define RELAY_TOPIC "on"
#define RELAY_PIN 12

class Relay: private Output {
  public:
    Relay(int pin, char* suffix, int *level) : level(level), Output(pin, RELAY_TOPIC, suffix) {};
    Relay(int pin, char* suffix) : Output(pin, RELAY_TOPIC, suffix) {};
    Relay(char* suffix) : Output(RELAY_PIN, RELAY_TOPIC, suffix) {};
    Relay(int pin) : Output(pin, RELAY_TOPIC) {};
    Relay() : Output(RELAY_PIN, RELAY_TOPIC) {};
    void setup();
    void set(int state);
    void set(uint8_t* payload, char* topic);
    char* get(char* output);
  private:
    int state;
    int *level = NULL;
};

#endif
