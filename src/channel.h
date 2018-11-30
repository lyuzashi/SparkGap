#ifndef channel_h
#define channel_h

#include <vector>
#include "setup.h"

class Channel : public Setup {
  public:
    Channel(int pin, char* topic, char* suffix, bool invert);
    Channel(int pin, char* topic, char* suffix);
    Channel(int pin, char* topic, bool invert);
    Channel(int pin, char* topic);
    char* topic;
    char* suffix = "";
    uint8_t pin;
    bool invert = false;
    void createTopic(char* output, char* method);
    void createTopic(char* output, char* method, char* suffix);
    virtual void setup() = 0;
    std::vector<char*> subscriptionTopics;
    void subscribe();
  private:
    void init();
};

#endif
