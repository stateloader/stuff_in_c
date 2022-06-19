#ifndef MODELS_H_
#define MODELS_H_

#include "configs.h"

typedef struct ConnModel {
  size id;
  int8_t set;
  char user[SBUFF];
  char pass[SBUFF];
} cmod_t;

typedef struct TempModel {
  int32_t id;
  int8_t set;
  char temp[SBUFF];
  char datm[TBUFF];
} tmod_t;

typedef struct DvceModel {
  int32_t id;
  int8_t set;
  int8_t led;
  char user[SBUFF];
  char datm[TBUFF];
} dmod_t;

typedef struct MesgModel {
  int32_t id;
  int8_t set;
  char user[SBUFF];
  char datm[TBUFF];
  char topc[SBUFF];
  char mesg[SBUFF];
} mmod_t;

#endif