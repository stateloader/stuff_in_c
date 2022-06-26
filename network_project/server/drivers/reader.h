/*------------------------------------------------------------------------------------------------------------------------
                                                                                                               READ HEADER
--------------------------------------------------------------------------------------------------------------------------
description to be
------------------------------------------------------------------------------------------------------------------------*/
#ifndef READER_H_
#define READER_H_

#include "configs.h"
#include "server.h"

typedef int8_t (*read_func)(server_t *server);

typedef struct ReadItem {
  const uint8_t table;
  read_func func;
} read_item;

int8_t read_driver(server_t *server);

inline static int8_t check_size_read(server_t *server, int32_t size_read) {
  if (server->size_recv != size_read) {
    System_Message("recived and written of different sizes");
    return FAIL;
  }
  return SUCC;
}

#endif