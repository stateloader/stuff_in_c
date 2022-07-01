#ifndef RECEIVE_H_
#define RECEIVE_H_

#include "configs.h"
#include "server.h"

int8_t receive_driver(server_t *server);

inline static int8_t protocol_obtain_check(server_t *server) {
  if (!check_term(server->pack, server->size_pack)) {
    Message_Info("package not nullterminated");
    server->session &= ~(1 << ALIVE);
    return FAIL;
  }
  return SUCC;
}

#endif