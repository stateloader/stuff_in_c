/*------------------------------------------------------------------------------------------------------------------------
                                                                                                               READ HEADER
--------------------------------------------------------------------------------------------------------------------------
description to be
------------------------------------------------------------------------------------------------------------------------*/
#ifndef READER_H_
#define READER_H_

#include "configs.h"

typedef struct ReadItem {
  const uint8_t model;
  const char *path;
} read_item;

typedef struct Reader {
  uint8_t status;
  read_item *item;
  int32_t size_file;
  char file_data[FBUFF];
  FILE *file;
} read_t;

int8_t read_driver(read_t *reader);

#endif