#ifndef default_h
#define default_h

#include <Arduino.h>
#include <functional>
#include "channel.h"

#define DEFAULT_TOPIC "default"

class Default: public Channel {
  public:
    Default(char* topic, char * suffix);
    Default(char* suffix);
    Default();
    int get();
    void setup();
    std::function<void(int value)> onChange;
  private:
    static int memoryLastIndex;
    static bool hasBegun;
    int memoryIndex;
    int value = NULL;
    char setTopic[50];
    bool wasUpdated;
    void init();
    void set(char* payload, char* topic);
};

#endif
