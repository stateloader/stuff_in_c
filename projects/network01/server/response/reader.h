#ifndef READER__H_
#define READER__H_

#include "../configs.h"

typedef struct ReadItem {
  const uint8_t flag;
  const char *filepath;
} read_item;

typedef struct Reader {
  size_t size_cont;
  uint8_t *protocol;
  char content[RBUFF];
  FILE *file;
} read_t;

void read_driver(read_t *reader);

#endif
