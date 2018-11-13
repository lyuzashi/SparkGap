#include <Arduino.h>
#include <vector>
#include <PubSubClient.h>

class MQTT {
  public:
    MQTT();
    void onMessage(void (*callback)(char*, uint8_t*, unsigned int));
    void onStateChange(void (*callback)(int));
    boolean loop();
    void setServer(IPAddress ip, uint16_t port);
    boolean subscribe(const char* topic);
    boolean connect(const char* id);
  private:
    std::vector<void (*)(char*, uint8_t*, unsigned int)> onMessageHandlers;
    std::vector<void (*)(int)> stateChange;
    void callbackMessage(char*, uint8_t*, unsigned int);
    int previousState;
    PubSubClient* client;
};
