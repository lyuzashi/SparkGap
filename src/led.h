#include <Arduino.h>
#include "output.h"
#include "mqtt.h"
#define OFF 0
#define ON 1
#define WINK 2
#define BLINK 3
#define BLINK_FAST 4

class LED: private Output {
  public:
    LED(int pin, char* topic, MQTT *mqtt);
    LED(int pin, MQTT *mqtt);
    void set(int state);
    uint8_t status();
  private:
    // uint8_t pin;
    // MQTT& _mqtt;
    // char* topic;
    // char setTopic[50];
    // String getTopic;
    String statusTopic;
    void handleMessage(char* topic, uint8_t* payload, unsigned int length);
    virtual void subscribe();
};
