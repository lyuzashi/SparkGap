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
    Relay(int pin, char* suffix, int *level) : level(level), Output(pin, RELAY_TOPIC, suffix, true) {};
    Relay(int pin, char* suffix) : Output(pin, RELAY_TOPIC, suffix, true) {};
    Relay(char* suffix) : Output(RELAY_PIN, RELAY_TOPIC, suffix, true) {};
    Relay(int pin) : Output(pin, RELAY_TOPIC, true) {};
    Relay() : Output(RELAY_PIN, RELAY_TOPIC, true) {};
    void setup();
    void set(int state);
    void set(char* payload, char* topic);
    char* get(char* output);
  private:
    int state;
    int *level = NULL;
};

#endif
