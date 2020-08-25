//#ifndef APP_UNTILS_H
//#define APP_UNTILS_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define timeout_init(timeout) (timeout) = millis();
bool timeout_check(uint32_t *from, uint32_t interval);