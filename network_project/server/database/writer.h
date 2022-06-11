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
  uint8_t request;
  data_item item;
  uint32_t package_size;
  uint32_t append_size;
  char package[MBUFF];
  FILE *file;
} write_t;

typedef uint8_t (*write_func)(write_t *writer);

typedef struct WriteDriverItem{
  const char *error_message;
  write_func func;
} write_item;

uint8_t database_writer(write_t *writer);

#endif