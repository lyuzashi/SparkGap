#include <ESP8266mDNS.h>
#include "defines.h"
#include "dnssd.h"

void DNSSD::setup() {
  updateState(DNSSD_STARTING);
  bool started = MDNS.begin(NAME);
  if (started) {
    updateState(DNSSD_IDLE);
  } else {
    updateState(DNSSD_FAILED);
  }
}

void DNSSD::find() {
  updateState(DNSSD_SEARCHING);
  int answers = MDNS.queryService(service, protocol);
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
  if (state != newState) {
    state = newState;
    for(unsigned int i = 0; i < stateChange.size(); ++i) {
      stateChange[i](newState);
    }
  }
}
