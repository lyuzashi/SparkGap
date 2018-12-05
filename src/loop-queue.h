// On end of loop myvector.clear();

#ifndef loop_queue_h
#define loop_queue_h

#include <Arduino.h>
#include <vector>
#include <functional>

class LoopQueue {
  public:
    static void onLoop(std::function<void()> callback);
    static void onEveryLoop(std::function<void()> callback);
    static boolean loop();
    static std::vector<std::function<void()>> onLoopHandlers;
    static std::vector<std::function<void()>> onEveryLoopHandlers;
};

#endif