/*------------------------------------------------------------------------------------------------------------------------
                                                                                                               READ HEADER
--------------------------------------------------------------------------------------------------------------------------
description to be
------------------------------------------------------------------------------------------------------------------------*/
#ifndef READER_H_
#define READER_H_

#include <stdint.h>
#include "sconfig.h"
#include "saker/models.h"

typedef struct Reader {
  int8_t model, action;
  int32_t rows_table;
  umod_t *table_user;
  smod_t *table_samp;
  dmod_t *table_dvce;
  mmod_t *table_mesg;
} read_t;

int8_t read_driver(read_t *reader);

#endif