#include "App_Untils.h"

bool timeout_check(uint32_t *from, uint32_t interval)
{
  if (millis() - (*from) >= interval) {
    *from = millis();
    return true;
  }
  return false;
}

