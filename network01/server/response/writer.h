#ifndef WRITER_H_
#define WRITER_H_

#include "../system/configs.h"

typedef struct Writer {
  size_t size_appd;
  uint8_t *protocol;
  char *append;
  FILE *file;
} write_t;

void write_driver(write_t *writer, uint16_t *state, uint16_t *error);

#endif