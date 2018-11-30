#ifndef input_h
#define input_h

#include "channel.h"

class Input : public Channel {
  public:
    Input(int pin, char* topic, char* suffix, bool invert);
    Input(int pin, char* topic, char* suffix);
    Input(int pin, char* topic, bool invert);
    Input(int pin, char* topic);
    virtual char* get(char* topic) = 0;
    void stateChange();
    int digitalRead();
  private:
    char getTopic[50];
    char statusTopic[70];
    void init();
};

#endif
