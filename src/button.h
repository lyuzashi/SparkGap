#ifndef button_h
#define button_h

#include <Arduino.h>
#include "input.h"

#define BUTTON_TOPIC "button"
#define BUTTON_PIN 0

#define IDLE 0
#define PRESS 1
#define LONG_PRESS 2

class Button: public Input {
  public:
    Button(int pin, char* suffix) : Input(pin, BUTTON_TOPIC, suffix, true) {};
    Button(char* suffix) : Input(BUTTON_PIN, BUTTON_TOPIC, suffix, true) {};
    Button(int pin) : Input(pin, BUTTON_TOPIC, true) {};
    Button() : Input(BUTTON_PIN, BUTTON_TOPIC, true) {};
    void setup();
    char* get(char* output);
  private:
    int rawState;
    bool bouncing;
    bool longPressing;
    void changed();
    bool debounce();
    void checkLongPress();
    unsigned long riseTime;
    const unsigned long LONG_DELTA = 3500ul;
    const unsigned long DEBOUNCE_DELTA = 20ul;
};

#endif
