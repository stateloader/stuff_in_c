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

typedef struct ReaderRouteItem{
  const char *wpackage;
  const char *filepath; 
} rrim_t;

typedef struct Reader {
  uint8_t route;
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