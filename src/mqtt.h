#ifndef mqtt_h
#define mqtt_h

#include <Arduino.h>
#include <vector>
#include <PubSubClient.h>

class MQTT {
  public:
    MQTT();
    void onMessage(std::function<void(char*, char*, unsigned int)> callback);
    void onStateChange(std::function<void(int)> callback);
    // void setServer(IPAddress ip, uint16_t port);
    boolean loop();
    // boolean subscribe(const char* topic);
    // boolean connect(const char* id);
    // boolean connect(const char* id, const char* user, const char* pass);
    static PubSubClient client;
    static MQTT instance;
  private:
    std::vector<std::function<void(char*, char*, unsigned int)>> onMessageHandlers;
    std::vector<std::function<void(int)>> stateChange;
    void callbackMessage(char*, uint8_t*, unsigned int);
    int previousState;
};

#endif