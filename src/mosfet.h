#ifndef mosfet_h
#define mosfet_h

#include <Arduino.h>
#include "output.h"

#define MOSFET_TOPIC "brightness"
#define MOSFET_PIN 12

// GPIO5	38  BLUE
// GPIO12	37  RED
// GPIO13	39  GREEN
// GPIO14	40  WHITE

class MOSFET: private Output {
  public:
    MOSFET(int pin, char* suffix) : Output(pin, MOSFET_TOPIC, suffix) {};
    MOSFET(char* suffix) : Output(MOSFET_PIN, MOSFET_TOPIC, suffix) {};
    MOSFET(int pin) : Output(pin, MOSFET_TOPIC) {};
    MOSFET() : Output(MOSFET_PIN, MOSFET_TOPIC) {};
    void setup();
    void set(int state);
    void set(char* payload, char* topic);
    char* get(char* output);
    int state;
  private:
};

#endif
