/*------------------------------------------------------------------------------------------------------------------------
                                                                                                               READ HEADER
--------------------------------------------------------------------------------------------------------------------------
description to be
------------------------------------------------------------------------------------------------------------------------*/
#ifndef READER_H_
#define READER_H_

#include <stdint.h>
#include "sconfig.h"

typedef struct UModel { 
  int32_t id;
  char username[SBUFF];
  char password[SBUFF];
} umod_t;

typedef struct SModel {
  int32_t id;
  char temp[SBUFF];
  char datm[TBUFF];
} smod_t;

typedef struct DModel {
  int32_t id;
  int8_t ledcolour;
} dmod_t;

typedef struct MModel {
  int32_t id;
  char username[SBUFF];
  char datetime[TBUFF];
  char topic[SBUFF];
  char message[SBUFF];
} mmod_t;

typedef struct Reader {
  umod_t *table_user;
  smod_t *table_samp;
  dmod_t *table_dvce;
  mmod_t *table_mesg;
} read_t;

int8_t read_driver(read_t *reader);

#endif