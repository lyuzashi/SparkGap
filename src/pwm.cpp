// #include <Arduino.h>
// #include "defines.h"
// #include "pwm.h"
// #include "mqtt.h"
// #include "types.h"
// #include "mqtt-smarthome.h"

// void PWM::setOn(int newState) {
//   if (newState == ON) {
//     digitalWrite(pin, LOW);
//   } else if (newState == OFF) {
//     analogWrite(pin, level);
//   }
//   if(newState != state) {
//     LED::stateChange();
//   }
//   state = newState;
// }

// void PWM::set(int newLevel) {
//   if (state == ON) {
//     analogWrite(pin, level);
//   }
//   if(newLevel != level) {
//     Output::stateChange();
//   }
//   level = newLevel;
// }

// void PWM::set(uint8_t* payload, char* topic) {
//   if (strcmp (topic, PWM_ON_TOPIC) == 0) {
//     setOn(atoi((const char*)payload));
//   } else if (strcmp (topic, PWM_TOPIC) == 0) {
//     set(atoi((const char*)payload));
//   }
// }

// char* PWM::get(char* topic) {
//   char buffer[16];
//   if (strcmp (topic, PWM_ON_TOPIC) == 0) {
//     return itoa(state, buffer, 10);
//   } else if (strcmp (topic, PWM_TOPIC) == 0) {
//     return itoa(level, buffer, 10);
//   }
// }
