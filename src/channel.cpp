#include "channel.h"
#include "mqtt.h"
#include "defines.h"
#include "types.h"
#include "mqtt-smarthome.h"

Channel::Channel(int pin, char* topic, MQTT *mqtt) : pin(pin), topic(topic), mqtt(mqtt) {
  // Call subscribe setup here

  // Input/output channels create their own topics, subscribe and register onMessage
  // listeners that ensure their topic matches and eventually calls a callback for get or set
  // These can be scoped to multiple inheritance with virtual inheritace to manage the
  // individual callbacks
  // https://stackoverflow.com/a/23231363/2530832

  // mqtt->onMessage([this] (char* topic, uint8_t* payload, unsigned int length) {
  //   this->handleMessage(topic, payload, length);
  //   // Both input and output classes should add their own onMessage calls, either to get or set,
  //   // with string comparison to provide just the appropriate topic
  //   // topic could be on or brightness for one thing e.g. a PWM
  //   // topic == statusTopic -> call get(topic)
  //   // get method in input needs to publish to status; and any time the state changes
  // });

  mqtt->onStateChange([this] (int mqttState) {
    if(mqttState == MQTT_CONNECTED) {
      // Input and output constructors could add to a list that gets subscribed to by this call
      // subscriptions:
      // * set (setTopic)
      // * get (getTopic, statusTopic)
      this->subscribe();
    } 
  });

  // This doesn't work because parent class is constructed first
  // try solution here: https://stackoverflow.com/a/962325
  // this->setup();

}

void Channel::createTopic(char* output, char* method) {
  char buffer[sizeof(TOP_LEVEL) + 1 + sizeof(method) + 1 + sizeof(NAME) + 1 + sizeof(topic)];
  strcpy(buffer, TOP_LEVEL);
  strcat(buffer, SP);
  strcat(buffer, method);
  strcat(buffer, SP);
  strcat(buffer, NAME);
  strcat(buffer, SP);
  strcat(buffer, topic);
  strcat(output, buffer);
}

void Channel::createTopic(char* output, char* method, char* suffix) {
  char buffer[sizeof(TOP_LEVEL) + 1 + sizeof(method) + 1 + sizeof(NAME) + 1 + sizeof(suffix) + 1 + sizeof(topic)];
  strcpy(buffer, TOP_LEVEL);
  strcat(buffer, SP);
  strcat(buffer, method);
  strcat(buffer, SP);
  strcat(buffer, NAME);
  strcat(buffer, " ");
  strcat(buffer, suffix);
  strcat(buffer, SP);
  strcat(buffer, topic);
  strcat(output, buffer);
}

void Channel::subscribe() {
  for(unsigned int i = 0; i < subscriptionTopics.size(); ++i) {
    mqtt->subscribe(subscriptionTopics[i]);
  }
}