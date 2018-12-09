#ifndef loop_queue_h
#define loop_queue_h

#include <Arduino.h>
#include <vector>
#include <list>
#include <functional>

class LoopQueue {
  private:
    struct onLoopHandler {
      std::function<void()> method;
      int delay;
      uint32_t start;
    };
    static std::list<onLoopHandler> onLoopHandlers;
    static bool evalIfReady(onLoopHandler& handler);
  public:
    static void onLoop(std::function<void()> callback);
    static void onLoop(std::function<void()> callback, int delay);
    static void onEveryLoop(std::function<void()> callback);
    static void loop();
    static std::vector<std::function<void()>> onEveryLoopHandlers;
};

#endif