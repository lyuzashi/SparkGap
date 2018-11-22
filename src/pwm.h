// Rather than trying to inherit in a diamond pattern, create two instances of output inside this 
// class and join them together with method calls.

// SO PWM will be a brightness class and MOSFET can extend LED and create an instance of PWM, 
// just overloading the LED set with PWM.level analogWrite

// #ifndef pwm_h
// #define pwm_h

// #include <Arduino.h>
// #include "led.h"
// #include "output.h"
// #include "mqtt.h"
// #define OFF 0
// #define ON 1

// #define PWM_ON_TOPIC "on"
// #define PWM_TOPIC "brightness"
// #define PWM_PIN 13

// class PWMOutput : virtual public Output {};

// class PWM : public LED, public PWMOutput {
//   public:
//     PWM(int pin, MQTT *mqtt) : LED(pin,PWM_ON_TOPIC, mqtt), PWMOutput(pin, PWM_TOPIC, mqtt) {};
//     void set(int level);
//     void setOn(int state);
//     void set(uint8_t* payload, char* topic);
//     char* get(char* topic);
//   private:
//     int level = 255; // This is the default "on" level
//     int state;
// };

// #endif
