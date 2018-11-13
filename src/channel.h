#include "mqtt.h"

class Channel {
  private:
    MQTT mqtt;
    String topic;
    int pin;
};
