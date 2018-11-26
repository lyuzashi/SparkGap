#ifndef channel_h
#define channel_h

#include <vector>
#include "setup.h"
#include "mqtt.h"

class Channel : public Setup {
  public:
    Channel(int pin, char* topic);
    Channel(int pin, char* topic, MQTT *mqtt);
    Channel(int pin, char* topic, char* suffix, MQTT *mqtt);
    char* topic;
    uint8_t pin;
    MQTT *mqtt;
    void createTopic(char* output, char* method);
    void createTopic(char* output, char* method, char* suffix);
    // virtual void handleMessage(char* topic, uint8_t* payload, unsigned int length) = 0;
    virtual void setup() = 0;
    std::vector<char*> subscriptionTopics;
    void subscribe();
  private:
    void init();
};

#endif
