#ifndef button_h
#define button_h

#include <Arduino.h>
#include "input.h"

#define BUTTON_TOPIC "button"
#define BUTTON_PIN 0

#define PRESS 1
#define LONG_PRESS 2

class Button: public Input {
  public:
    Button(int pin, char* suffix) : Input(pin, BUTTON_TOPIC, suffix) {};
    Button(char* suffix) : Input(BUTTON_PIN, BUTTON_TOPIC, suffix) {};
    Button(int pin) : Input(pin, BUTTON_TOPIC) {};
    Button() : Input(BUTTON_PIN, BUTTON_TOPIC) {};
    void setup();
    char* get(char* output);
  private:
    // int state;
    void changed();
    unsigned long riseTime;
    const unsigned long LONG_DELTA = 1000ul;
    const unsigned long DEBOUNCE_DELTA = 20ul;
};

#endif
