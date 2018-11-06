#include <cstddef>
#include "../libraries/callback/Callback.h"
#define WPS_FAILED -2
#define WIFI_DISCONNECTED -1
#define WPS_CONNECTED 0
#define WIFI_CONNECTING 1
#define WPS_CONNECTING 2

class WPS {
  public:
    WPS();
    void loop();
    void setup();
    void reset();
    void setCallback(FunctionSlot<int> callback);
  private:
    int state;
    Signal<int> stateChange;
    void updateState(int newState);
    bool wpsConnected;
    void reconnect();
};
