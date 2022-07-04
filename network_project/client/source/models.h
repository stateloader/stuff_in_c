#ifndef MODELS_H_
#define MODELS_H_

#include "config.h"

typedef struct MesgModel {
  uint32_t id;
  int8_t user[SBUFF];
  int8_t datm[TBUFF];
  int8_t topc[SBUFF];
  int8_t mesg[SBUFF];
} mmod_t;

typedef struct DvceModel {
  uint32_t id;
  int8_t user[SBUFF];
  int8_t datm[TBUFF];
  int8_t init[TBUFF];
} dmod_t;

#endif