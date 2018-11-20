#ifndef setup_h
#define setup_h

#include <vector>

std::vector<std::function<void()>> setupMethods;

class Setup {
  public:
    static void setup();
    virtual void setup() = 0;
};


#endif
