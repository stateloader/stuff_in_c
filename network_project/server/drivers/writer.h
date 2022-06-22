#ifndef WRITER_H_
#define WRITER_H_

#include "configs.h"

typedef struct WriteItem {
  const uint8_t model;
  const char *path;
} write_item;

typedef struct Writer {
  uint8_t status;
  write_item *item;
  int32_t size_appd;
  char appd[SBUFF];
  char resp[SBUFF];
  FILE *file;
} write_t;

int8_t write_driver(write_t *writer);


#endif