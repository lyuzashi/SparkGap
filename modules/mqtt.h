#include <vector>
#include <PubSubClient.h>

class MQTT: public PubSubClient {
  public:
    MQTT();
    void onMessage(void (*callback)(char*, uint8_t*, unsigned int));
    // void onMessage(FunctionSlot<char*, uint8_t*, unsigned int> callback);
    // void onStateChange(FunctionSlot<int> callback);
  private:
    std::vector<void (*)(char*, uint8_t*, unsigned int)> onMessageHandlers;
    void callbackMessage(char*, uint8_t*, unsigned int);
};