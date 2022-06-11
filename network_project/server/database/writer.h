#ifndef WRITER_H_
#define WRITER_H_

#include <stddef.h>
#include <stdint.h>
#include "dbconfig.h"

typedef struct DataItem {
  uint8_t model;
  const char *file_path;
} data_item;

typedef struct WriteDriver {
  data_item item;
  size_t psize, asize;
  char package[MBUFF];
  FILE *file;
} write_t;

uint8_t database_writer(write_t *writer, uint8_t request);

#endif