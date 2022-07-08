#ifndef WRITER_H_
#define WRITER_H_

#include "../configs.h"

typedef struct Writer {
  uint8_t *protocol;
  size_t size_pack;
  char *package;
  FILE *file;
} write_t;

void write_driver(write_t *writer, uint16_t *state, uint16_t *error);

#endif