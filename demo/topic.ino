#include <Arduino.h>


#define TOP_LEVEL "relays"
#define SET "set"

#define SET_TOPIC TOP_LEVEL "/" SET "/" NAME "/"



#define TOPIC "led"

void composeSetTopic(const char* topic, char* composite) {

  char buffer[sizeof(SET_TOPIC) + sizeof(topic)];

  strcpy(buffer, SET_TOPIC);
  strcat(buffer, topic);
  strcpy(composite, buffer);
}


void setup() {
  Serial.begin(115200);
}

void loop() {
  delay(1000);
  // const char* topic = TOPIC;
  // char buffer[sizeof(SET_TOPIC) + sizeof(topic)];
  // strncpy(buffer, SET_TOPIC, sizeof(SET_TOPIC));
  // strncat(buffer, topic, sizeof(topic));

  // Serial.println(buffer);

  char setTopic[] = {};

  composeSetTopic(TOPIC, setTopic);

  Serial.println(setTopic);
}
