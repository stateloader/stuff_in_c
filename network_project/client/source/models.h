#ifndef MODELS_H_
#define MODELS_H_

#include "configs.h"

typedef struct MesgModel {
  int8_t user[SBUFF];
  int8_t datm[TBUFF];
  int8_t topc[SBUFF];
  int8_t mesg[SBUFF];
} mmod_t;

typedef struct DvceModel {
  int8_t led;
  int8_t user[SBUFF];
  int8_t datm[TBUFF];
} dmod_t;

#endif