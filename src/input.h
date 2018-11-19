#include "channel.h"
#include "mqtt.h"

class Input : public Channel {
  public:
    Input(int pin, char* topic, MQTT *mqtt) : Channel(pin, topic, mqtt) {};
    char getTopic[50];
    char statusTopic[50];
    void createGetTopic(char* output);
    void createGetTopic(char* output, char* suffix);
    void createStatusTopic(char* output);
    void createStatusTopic(char* output, char* suffix);
};
