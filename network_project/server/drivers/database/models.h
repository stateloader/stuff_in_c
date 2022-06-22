#ifndef MODELS_H_
#define MODELS_H_

#include <stdint.h>
#include "../configs.h"

inline static int8_t fileopen_check(FILE *file) {
  if (!file) {
    System_Message("failed to open file");
    return FAIL;
  }
  return SUCC;
}
#endif