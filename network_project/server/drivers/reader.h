/*------------------------------------------------------------------------------------------------------------------------
                                                                                                               READ HEADER
--------------------------------------------------------------------------------------------------------------------------
description to be
------------------------------------------------------------------------------------------------------------------------*/
#ifndef READER_H_
#define READER_H_

#include <stdint.h>
#include "sconfig.h"

typedef struct UserModel { 
  int32_t id;
  char user[SBUFF];
  char pass[SBUFF];
} umod_t;

typedef struct SampModel {
  int32_t id;
  char temp[SBUFF];
  char datm[TBUFF];
} smod_t;

typedef struct DvceModel {
  int32_t id;
  int8_t led;
} dmod_t;

typedef struct MesgModel {
  int32_t id;
  char user[SBUFF];
  char datm[TBUFF];
  char topc[SBUFF];
  char mesg[SBUFF];
} mmod_t;

typedef struct Reader {
  int8_t status;
  int32_t rows_tbusr;
  int32_t rows_tsmpl;
  int32_t rows_tdvce;
  int32_t rows_tmesg;
  umod_t *table_user;
  smod_t *table_samp;
  dmod_t *table_dvce;
  mmod_t *table_mesg;
} read_t;

int8_t read_driver(read_t *reader);

#endif