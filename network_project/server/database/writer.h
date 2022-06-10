#ifndef WRITER_H_
#define WRITER_H_

#include "database.h"

typedef struct DataItem {
  uint8_t model;
  const char *file_path;
} data_item;

typedef struct WriteDriver {
  data_item item;
  FILE *file;
} write_t;

#endif