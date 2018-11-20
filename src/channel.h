#include <vector>
#include "mqtt.h"
//toplevelname, method, item, interfaces
class Channel {
  public:
    Channel(int pin, char* topic, MQTT *mqtt);
    Channel(int pin, char* topic, char* suffix, MQTT *mqtt);
    char* topic;
    uint8_t pin;
    MQTT *mqtt;
    void createTopic(char* output, char* method);
    void createTopic(char* output, char* method, char* suffix);
    virtual void handleMessage(char* topic, uint8_t* payload, unsigned int length) = 0;
    virtual void setup() = 0;
    std::vector<char*> subscriptionTopics;
    void subscribe();
};
