#include "input.h"
#include "mqtt-smarthome.h"

void Input::createGetTopic(char* output) {
  createTopic(output, GET);
}

void Input::createGetTopic(char* output, char* suffix) {
  createTopic(output, GET, suffix);
}

void Input::createStatusTopic(char* output) {
  createTopic(output, STATUS);
}

void Input::createStatusTopic(char* output, char* suffix) {
  createTopic(output, STATUS, suffix);
}


