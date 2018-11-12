#include <Arduino.h>
#include <vector>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

class MQTT: public PubSubClient {
  public:
    MQTT(WiFiClient client);
    void onMessage(void (*callback)(char*, uint8_t*, unsigned int));
    // void onMessage(FunctionSlot<char*, uint8_t*, unsigned int> callback);
    // void onStateChange(FunctionSlot<int> callback);
  private:
    std::vector<void (*)(char*, uint8_t*, unsigned int)> onMessageHandlers;
    void callbackMessage(char*, uint8_t*, unsigned int);
};
