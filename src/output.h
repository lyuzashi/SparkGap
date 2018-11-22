#ifndef output_h
#define output_h

#include "input.h"
#include "mqtt.h"

class Output : public Input {
  public:
    Output(int pin, char* topic, char* suffix, MQTT *mqtt);
    Output(int pin, char* topic, MQTT *mqtt);
    virtual void set(uint8_t* payload, char* topic) = 0;
  private:
    char setTopic[50];
    void init();
};

#endif
