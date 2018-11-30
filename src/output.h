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
    bool invert = false;
  private:
    char setTopic[50];
    void init();
};

#endif
