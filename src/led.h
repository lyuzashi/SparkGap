#include <Arduino.h>
#include "mqtt.h"
#define OFF 0
#define ON 1
#define WINK 2
#define BLINK 3
#define BLINK_FAST 4

class LED {
  public:
    LED(int pinNumber, const char* topicName, MQTT *mqtt);
    void set(int state);
    uint8_t status();
  private:
    uint8_t pin;
    String topic;
    String setTopic;
    String getTopic;
    String statusTopic;
    void handleMessage(char* topic, uint8_t* payload, unsigned int length);
};
