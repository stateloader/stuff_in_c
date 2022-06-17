#ifndef RECIEVED_H_
#define RECIEVED_H_

#include <stdint.h>
#include "sconfig.h"
#include "server.h"

int8_t recieved_driver(server_t *server);

inline static int8_t recieved_check(server_t *server) {

  if (!check_term(server->recv, server->size_recv)) {
    System_Message("Recvied request isn't terminated");
    return FAIL;
  } else if (!check_tedl(server->recv, server->size_recv)) {
    System_Message("Third last byte isn't delimiter.");
    return FAIL;
  }
  fetch_endb(server->endbyte, server->recv, server->size_recv);
  return SUCC;
}
#endif