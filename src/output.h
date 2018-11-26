#ifndef output_h
#define output_h

#include "input.h"

class Output : public Input {
  public:
    Output(int pin, char* topic, char* suffix);
    Output(int pin, char* topic);
    virtual void set(uint8_t* payload, char* topic) = 0;
  private:
    char setTopic[50];
    void init();
};

#endif
