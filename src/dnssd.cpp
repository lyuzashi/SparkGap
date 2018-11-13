#include <ESP8266mDNS.h>
#include "defines.h"
#include "dnssd.h"

DNSSD::DNSSD(char *service, char *protocol) {
  _service = service;
  _protocol = protocol;
}

void DNSSD::setup() {
  Serial.println("starting discovery");
  updateState(DNSSD_STARTING);
  Serial.println("now!");
  bool started = MDNS.begin(NAME);
  Serial.println("discovery started");
  if (started) {
    updateState(DNSSD_IDLE);
  } else {
    updateState(DNSSD_FAILED);
  }
}

void DNSSD::find() {
  Serial.println("search started");
  updateState(DNSSD_SEARCHING);
  Serial.println("now!");
  int answers = MDNS.queryService(_service, _protocol);
  if (answers == 0) {
    updateState(DNSSD_NOT_FOUND);
  } else {
    ip = MDNS.IP(0);
    port = MDNS.port(0);
    updateState(DNSSD_FOUND);
  }
}

void DNSSD::forget() {
  ip = INADDR_NONE;
  port = 0;
  updateState(DNSSD_IDLE);
}

void DNSSD::setCallback(void (*callback)(int)) {
  stateChange.push_back(callback);
}

void DNSSD::updateState(int newState) {
  Serial.printf("DNS state update %d\n", newState);
  if (state != newState) {
    state = newState;
    for(unsigned int i = 0; i < stateChange.size(); ++i) {
      stateChange[i](newState);
    }
  }
}
