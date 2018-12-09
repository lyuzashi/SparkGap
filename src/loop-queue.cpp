#include <Arduino.h>
#include <vector>
#include <list>
#include <functional>
#include "loop-queue.h"

std::list<LoopQueue::onLoopHandler> LoopQueue::onLoopHandlers;
std::vector<std::function<void()>> LoopQueue::onEveryLoopHandlers;

void LoopQueue::onLoop(std::function<void()> callback) {
  onLoopHandler handler;
  handler.method = callback;
  handler.delay = 0;
  onLoopHandlers.push_back(handler);
}

void LoopQueue::onLoop(std::function<void()> callback, int delay) {
  onLoopHandler handler;
  handler.method = callback;
  handler.delay = delay;
  handler.start = millis();
  onLoopHandlers.push_back(handler);
}

void LoopQueue::onEveryLoop(std::function<void()> callback) {
  onEveryLoopHandlers.push_back(callback);
}

bool LoopQueue::evalIfReady(onLoopHandler& handler) {
  if (handler.delay == 0 || millis() - handler.start >= handler.delay) {
    handler.method();
    return true;
  }
  return false;
}

void LoopQueue::loop() {
  onLoopHandlers.remove_if(LoopQueue::evalIfReady);
  for(unsigned int i = 0; i < onEveryLoopHandlers.size(); ++i) {
    onEveryLoopHandlers[i]();
  }
}
