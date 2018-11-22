#include "setup.h"

std::vector<Setup*> Setup::setupMethods;

Setup::Setup() {
  Setup::setupMethods.push_back(this);
};

void Setup::run() {
  for(unsigned int i = 0; i < Setup::setupMethods.size(); ++i) {
    Setup::setupMethods[i]->setup();
  }
};
