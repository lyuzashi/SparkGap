#include <ESP8266mDNS.h>
#include "dnssd.h"

DNSSD::DNSSD(char *service, char *protocol) {
  _service = service;
  _protocol = protocol;
}

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
  state = DNSSD_SEARCHING;
  int answers = MDNS.queryService(_service, _protocol);
  if (answers == 0) {
    updateState(DNSSD_NOT_FOUND);
  } else {
    ip = MDNS.IP(0);
    port = MDNS.port(0);
    updateState(DNSSD_FOUND);
  }
}

void DNSSD::setCallback(FunctionSlot<int> callback) {
  stateChange.attach(callback);
}

void DNSSD::updateState(int newState) {
  if (state != newState) {
    state = newState;
    stateChange.fire(state);
  }
}