#ifndef input_h
#define input_h

#include "channel.h"
#include "mqtt.h"

class Input : public Channel {
  public:
    Input(int pin, char* topic, char* suffix, MQTT *mqtt);
    Input(int pin, char* topic, MQTT *mqtt);
    virtual char* get(char* topic) = 0;
    void stateChange(char* state, char* topic);
  private:
    char getTopic[50];
    char statusTopic[50];
    void init();
};

#endif
