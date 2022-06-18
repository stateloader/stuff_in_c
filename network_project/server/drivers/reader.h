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

typedef struct ReadItem {
  const char *path;
} read_item;

typedef struct Reader {
  uint8_t status;
  int8_t model, action;
  int32_t rows_table;
  cmod_t *table_conn;
  tmod_t *table_temp;
  dmod_t *table_dvce;
  mmod_t *table_mesg;
  void *table;
} read_t;

int8_t read_driver(read_t *reader);

#endif