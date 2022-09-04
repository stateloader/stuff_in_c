#ifndef WRITER__H_
#define WRITER__H_

#include "../configs.h"

typedef struct Writer {
  size_t size_push;
  uint8_t *protocol;
  char *append;
  FILE *file;
} write_t;

void write_driver(write_t *writer);

#endif
