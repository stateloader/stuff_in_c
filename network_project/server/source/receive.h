#ifndef RECEIVE_H_
#define RECEIVE_H_

#include "config.h"
#include "server.h"

int8_t receive_driver(server_t *server);

inline static int8_t protocol_obtain_checks(server_t *server) {

  if (server->pack[server->size_pack - 1] != '\0') {
    System_Message("package not nullterminated.");
    return FAIL;
  }
  if (server->pack[TBYTE] & (0 << UNBIT)) {
    System_Message("TBYTE not unsigned");
    return FAIL;
  }
  if (server->pack[ABYTE] & (0 << UNBIT)) {
    System_Message("ABYTE not unsigned");
    return FAIL;
  }
  if (server->pack[SBYTE] & (0 << UNBIT)) {
    System_Message("SBYTE not unsigned");
    return FAIL;
  }
  return SUCC;
}

#endif