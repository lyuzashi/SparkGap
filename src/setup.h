#ifndef setup_h
#define setup_h

#include <Arduino.h>
#include <vector>

class Setup {
  public:
    Setup();
    static void run();
    static std::vector<Setup*> setupMethods;
    virtual void setup() = 0;
};

#endif
