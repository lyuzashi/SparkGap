// On end of loop myvector.clear();

#ifndef loop_queue_h
#define loop_queue_h

#include <Arduino.h>
#include <vector>
#include <functional>

class LoopQueue {
  public:
    static void onLoop(std::function<void()> callback);
    static boolean loop();
  private:
    static std::vector<std::function<void()>> onLoopHandlers;
};

#endif