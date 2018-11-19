#include "input.h"
#include "mqtt.h"

class Output : public Input {
  public:
    Output(int pin, char* topic, MQTT *mqtt) : Input(pin, topic, mqtt) {};
    char setTopic[50];
};
