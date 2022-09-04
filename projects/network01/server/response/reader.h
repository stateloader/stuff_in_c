#ifndef READER__H_
#define READER__H_

#include "../configs.h"

typedef struct Reader {
  size_t size_pull;
  uint8_t *protocol;
  char read[RBUFF];
  FILE *file;
} read_t;

void read_driver(read_t *reader);

#endif
