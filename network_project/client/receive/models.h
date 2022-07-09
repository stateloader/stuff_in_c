#ifndef MODELS_H_
#define MODELS_H_

#include "../system/configs.h"

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
  int8_t datm[SBUFF];
  int8_t push[SBUFF];
} dmod_t;

mmod_t *table_mesg_create(
  const char *package, size_t size_pack, size_t rows, uint8_t *state, uint16_t *error);
  
dmod_t *table_dvce_create(
  const char *package, size_t size_pack, size_t rows, uint8_t *state, uint16_t *error);

#endif
