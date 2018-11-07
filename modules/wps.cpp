#include "wps.h"
#include <ESP8266WiFi.h>

WPS::WPS() {
  WiFi.hostname(NAME);
  WiFi.mode(WIFI_STA);
}

void WPS::loop() {
  wl_status_t status = WiFi.status();

  // No stored credentials to attempt to connect with.
  if (status == WL_IDLE_STATUS && state != WPS_CONNECTING) {
    setup();
  }

  // Credentails stored, attempt to connect.
  if (status == WL_DISCONNECTED && state != WIFI_CONNECTING) {
    reconnect();
  }

  // Try set up with WPS if unable to connect with stored credentials
  if (status == WL_CONNECT_FAILED && state != WPS_CONNECTING) {
    setup();
  }

    // Attempt to reconnect if lost
  if (status == WL_CONNECTION_LOST && state != WIFI_CONNECTING) {
    reconnect();
  }

  // Connected!
  if (status == WL_CONNECTED) {
    updateState(WPS_CONNECTED);
  }

}

void WPS::setup() {
  updateState(WPS_CONNECTING);
  bool wpsSuccess = WiFi.beginWPSConfig();
  if(wpsSuccess) {
    if(WiFi.SSID().length() > 0) {
      updateState(WPS_CONNECTED);
    } else {
      updateState(WPS_FAILED);
    }
  }
}

void WPS::reset() {
  WiFi.disconnect();
  // Might need ESP.reset() too?
}

void WPS::setCallback(void (*callback)(int)) {
  stateChange.push_back(callback);
}

void WPS::updateState(int newState) {
  if (state != newState) {
    state = newState;
    for(unsigned int i = 0; i < stateChange.size(); ++i) {
      stateChange[i](newState);
    }
  }
}

void WPS::reconnect () {
  updateState(WIFI_CONNECTING);
  WiFi.begin(WiFi.SSID().c_str(), WiFi.psk().c_str());
}