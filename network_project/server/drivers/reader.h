/*------------------------------------------------------------------------------------------------------------------------
                                                                                                               READ HEADER
--------------------------------------------------------------------------------------------------------------------------
description to be
------------------------------------------------------------------------------------------------------------------------*/
#ifndef READER_H_
#define READER_H_

#include "config.h"
#include "server.h"

typedef int8_t (*read_func)(server_t *server);

typedef struct ReadItem {
  const uint8_t flag;
  read_func func;
} read_item;

int8_t database_reader(server_t *server);

inline static int8_t reader_file_open_check(server_t *server) {
  if (server->dbfile == NULL) {
    server->session |= (1 << RPROB);
    System_Message("failed to open file");
    return FAIL;
  }
  return SUCC;
}

inline static int8_t reader_file_data_check(server_t *server) {
  if (server->size_resp < 4) {
    server->session |= (1 << RPROB);
    System_Message("to little something reader file");
    return FAIL;
  }
  return SUCC;
}

#endif