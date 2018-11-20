#include "input.h"
#include "mqtt.h"

class Output : public Input {
  public:
    Output(int pin, char* topic, char* suffix, MQTT *mqtt) : Input(pin, topic, suffix, mqtt) {};
    Output(int pin, char* topic, MQTT *mqtt) : Input(pin, topic, mqtt) {};
    virtual void set(uint8_t* payload, char* topic) = 0;
  private:
    char setTopic[50];
};
