#ifndef MODELS_H_
#define MODELS_H_

#include "configs.h"

typedef struct DvceModel {
  size_t id;
  int8_t set;
  int8_t led;
  char user[SBUFF];
  char datm[TBUFF];
} dmod_t;

typedef struct MesgModel {
  size_t id;
  int8_t set;
  char user[SBUFF];
  char datm[TBUFF];
  char topc[SBUFF];
  char mesg[SBUFF];
} mmod_t;

#endif