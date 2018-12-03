#include <Arduino.h>
#include <vector>
#include "loop-queue.h"

void LoopQueue::onLoop(std::function<void()> callback) {
  onLoopHandlers.push_back(callback);
}

boolean LoopQueue::loop() {
  for(unsigned int i = 0; i < onLoopHandlers.size(); ++i) {
    onLoopHandlers[i]();
  }
  onLoopHandlers.clear();
}
