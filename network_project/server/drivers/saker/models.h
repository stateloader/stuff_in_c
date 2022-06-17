#ifndef MODELS_H_
#define MODELS_H_

#include <stdint.h>
#include "../sconfig.h"

typedef struct UserModel {      // 3
  int32_t id;
  int8_t set;
  char user[SBUFF];
  char pass[SBUFF];
} umod_t;

typedef struct SampModel {      // 3
  int32_t id;
  int8_t set;
  char temp[SBUFF];             // stnd size.
  char datm[TBUFF];
} smod_t;

typedef struct DvceModel {      // 4
  int32_t id;
  int8_t set;
  char user[SBUFF];
  char datm[TBUFF];
  int8_t ledcolour;
} dmod_t;

typedef struct MesgModel {      // 5
  int32_t id;
  int8_t set;
  char user[SBUFF];
  char datm[TBUFF];
  char topc[SBUFF];
  char mesg[SBUFF];
} mmod_t;

#endif