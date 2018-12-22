#ifndef output_h
#define output_h

#include "input.h"

class Output : public Input {
  public:
    Output(int pin, char* topic, char* suffix, bool invert);
    Output(int pin, char* topic, char* suffix);
    Output(int pin, char* topic, bool invert);
    Output(int pin, char* topic);
    virtual void set(char* payload, char* topic) = 0;
    void digitalWrite(uint8_t value);
    void analogWrite(int value);
  private:
    char setTopic[50];
    void init();
    void update();
    float start;
    float destination;
    float startTime;
    float transitionTime = 500;
    int transitioningState;
    bool isTransitionining;
};

#endif
