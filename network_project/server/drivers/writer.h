#ifndef WRITER_H_
#define WRITER_H_

#include "configs.h"
#include "server.h"

typedef int8_t (*write_func)(server_t *server);

typedef struct WriteItem {
  const uint8_t model;
  write_func func;
} write_item;

int8_t database_writer(server_t *server);

inline static int8_t check_file_open(server_t *server) {
  if (!server->dbfile) {
    System_Message("couldn't open database. Let's panic a bit.");
    return FAIL;
  }
  return SUCC;
}
inline static int8_t check_size_appd(server_t *server, int32_t size_write) {
  if (server->size_pack != size_write) {
    System_Message("recived and written of different sizes");
    return FAIL;
  }
  return SUCC;
}
#endif