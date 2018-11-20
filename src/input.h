#ifndef input_h
#define input_h

#include "channel.h"
#include "mqtt.h"

class Input : public Channel {
  public:
    Input(int pin, char* topic, char* suffix, MQTT *mqtt) : Channel(pin, topic, suffix, mqtt) {};
    Input(int pin, char* topic, MQTT *mqtt) : Channel(pin, topic, mqtt) {};
    void createGetTopic(char* output);
    void createGetTopic(char* output, char* suffix);
    void createStatusTopic(char* output);
    void createStatusTopic(char* output, char* suffix);
    virtual void get(char* topic) = 0;
  private:
    char getTopic[50];
    char statusTopic[50];
};

#endif
