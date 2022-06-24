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

inline static void check_file_open(server_t *server) {
  if (!server->dbfile) {
    System_Message("couldn't open database. Let's panic a bit.");
    server->status = - 1;
  }
}

inline static void check_size_appd(server_t *server, int32_t size_write) {
  if (server->size_recv != size_write) {
    System_Message("recived and written of different sizes");
    server->status = - 1;
  }
}
#endif