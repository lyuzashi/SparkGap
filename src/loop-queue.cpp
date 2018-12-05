#include <Arduino.h>
#include <vector>
#include <functional>
#include "loop-queue.h"

std::vector<std::function<void()>> LoopQueue::onLoopHandlers;
std::vector<std::function<void()>> LoopQueue::onEveryLoopHandlers;

void LoopQueue::onLoop(std::function<void()> callback) {
  onLoopHandlers.push_back(callback);
}

void LoopQueue::onEveryLoop(std::function<void()> callback) {
  onEveryLoopHandlers.push_back(callback);
}

boolean LoopQueue::loop() {
  for(unsigned int i = 0; i < onLoopHandlers.size(); ++i) {
    onLoopHandlers[i]();
  }
  onLoopHandlers.clear();
  for(unsigned int i = 0; i < onEveryLoopHandlers.size(); ++i) {
    onEveryLoopHandlers[i]();
  }
}
