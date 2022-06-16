#ifndef RECIEVED_H_
#define RECIEVED_H_

#include <stdint.h>
#include "sconfig.h"
#include "server.h"

int8_t recieved_driver(server_t *server);

inline static int8_t recieved_check(server_t *server) {
  if (!check_term(server->recv, server->size_recv)) {
    System_Message("recvied request isn't terminated");
    return FAIL;
  }
  return SUCC;
}

#endif