#ifndef button_h
#define button_h

#include <Arduino.h>
#include "input.h"

#define BUTTON_TOPIC "button"
#define BUTTON_PIN 0

class Button: public Input {
  public:
    Button(int pin, char* suffix) : Input(pin, BUTTON_TOPIC, suffix) {};
    Button(char* suffix) : Input(BUTTON_PIN, BUTTON_TOPIC, suffix) {};
    Button(int pin) : Input(pin, BUTTON_TOPIC) {};
    Button() : Input(BUTTON_PIN, BUTTON_TOPIC) {};
    void setup();
    char* get(char* output);
  private:
    int state;
    void changed();
    unsigned long riseTime;
    const unsigned long LONG_DELTA = 2000ul;
    const unsigned long DEBOUNCE_DELTA = 100ul;
};

#endif
