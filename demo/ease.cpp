#include <iostream>
#include <cstdlib>
#include <sys/timeb.h>
#include <math.h> 
#include <unistd.h>
using namespace std;

float start;
float destination;
float startTime;
float transitionTime = 1000;

unsigned long millis() {
  timeb tb;
  ftime(&tb);
  int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
  return nCount;
}

float linear(float t) {
  return t;
}
float easeInQuad(float t) {
  return t * t;
}
float easeOutQuad(float t) {
  return t * (2 - t);
}
float easeInOutQuad(float t) {
  return t < 0.5 ? 2 * t * t : -1 + (4 - 2 * t) * t;
}

void ease(int value) {
  start = 500;
  destination = (float)value;
  startTime = (float)millis();
}

bool update() {
  float now = (float)millis();
  float time = std::min((float)1, ((now - startTime) / transitionTime));
  float timeFunction = easeOutQuad(time);
  float val = ceil((timeFunction * (destination - start)) + start); 
  cout << val << endl;
  return val == destination;
}


int main() {
  ease(100);
  cout << "Start: " << startTime << endl;
  do {
    usleep(5000);
  } while (!update());
  return 0;
}