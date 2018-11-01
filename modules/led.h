#include <Arduino.h>
#define OFF 0
#define ON 1
#define WINK 2
#define BLINK 3
#define BLINK_FAST 4

class LED {
  public:
    LED(int pinNumber, const char* topicName);
    void state(int state);
  private:
    uint8_t pin;
    const char* topic;
    const char* setTopic;
    const char* getTopic;
    const char* statusTopic;
};
