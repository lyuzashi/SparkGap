#include <Arduino.h>
#include <vector>
#include <ESP8266mDNS.h>
#define DNSSD_FAILED -2
#define DNSSD_NOT_FOUND -1
#define DNSSD_FOUND 0
#define DNSSD_IDLE 1
#define DNSSD_SEARCHING 2
#define DNSSD_STARTING 3

class DNSSD {
  public:
    DNSSD(char *service, char *protocol);
    void setup();
    void find();
    IPAddress ip;
    uint16_t port;
    void setCallback(void (*callback)(int));
  private:
    int state;
    std::vector<void (*)(int)> stateChange;
    void updateState(int newState);
    char* _service;
    char* _protocol;
};
