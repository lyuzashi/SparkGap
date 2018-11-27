#ifndef motion_h
#define motion_h

#include <Arduino.h>
#include "input.h"

#define MOTION_TOPIC "motion"
#define MOTION_PIN 15

class Motion: public Input {
  public:
    Motion(int pin, char* suffix) : Input(pin, MOTION_TOPIC, suffix) {};
    Motion(char* suffix) : Input(MOTION_PIN, MOTION_TOPIC, suffix) {};
    Motion(int pin) : Input(pin, MOTION_TOPIC) {};
    Motion() : Input(MOTION_PIN, MOTION_TOPIC) {};
    void setup();
    char* get(char* output);
  private:
    int state;
    void changed();
};

#endif
