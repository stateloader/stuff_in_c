#ifndef WRITER_H_
#define WRITER_H_

#include "database.h"

typedef struct DataItem {
  uint8_t model;
  const char *file_path;
} data_item;

typedef struct WriteDriver {
  data_item item;
  size_t package_size;
  size_t append_size;
  char package[MBUFF];
  FILE *file;
} write_t;

uint8_t database_writer(uint8_t request, write_t *writer);

#endif