#ifndef READER_H_
#define READER_H_

#include "../configs.h"

typedef struct Reader {
  size_t size_cont;
  uint8_t *protocol;
  char content[RBUFF];
  FILE *file;
} read_t;

void read_driver(read_t *reader, uint16_t *state, uint16_t *error);

#endif