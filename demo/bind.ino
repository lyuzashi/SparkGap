#include <Arduino.h>
#include <functional>

void attach(std::function<void(void)> cb) { cb(); }

class T {
  public:
    T(char* out);
  private:
    // static void runCb(T*);
    void callback();
    char* out;
};

T::T(char* out) : out(out) {
  attach(std::bind(&T::callback, this));
}

void T::callback() {
  Serial.println(out);
}
 
 T t("ok");
 

void setup() {
  Serial.begin(115200);
}

void loop() {
}