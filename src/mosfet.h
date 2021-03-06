#ifndef mosfet_h
#define mosfet_h

#include <Arduino.h>
#include "output.h"
#include "relay.h"
#include "default.h"

#define MOSFET_TOPIC "brightness"
#define MOSFET_PIN 12

// GPIO5	38  BLUE
// GPIO12	37  RED
// GPIO13	39  GREEN
// GPIO14	40  WHITE

class MOSFET: public Output {
  public:
    MOSFET(int pin, char* suffix) : defaultBrightness(suffix), Output(pin, MOSFET_TOPIC, suffix) {};
    MOSFET(char* suffix) : defaultBrightness(suffix), Output(MOSFET_PIN, MOSFET_TOPIC, suffix) {};
    MOSFET(int pin) : defaultBrightness(), Output(pin, MOSFET_TOPIC) {};
    MOSFET() : defaultBrightness(), Output(MOSFET_PIN, MOSFET_TOPIC) {};
    void setup();
    void set(int state);
    void set(char* payload, char* topic);
    char* get(char* output);
    void linkRelay(Relay* relay);
  private:
    int *switchState = NULL;
    int relayState;
    Default defaultBrightness;
};

#endif
