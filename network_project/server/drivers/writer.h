#ifndef WRITER_H_
#define WRITER_H_

#include "configs.h"
#include "server.h"

typedef void (*write_func)(server_t *server);

typedef struct WriteItem {
  const uint8_t model;
  write_func func;
} write_item;

void write_driver(server_t *server);

#endif