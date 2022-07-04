#ifndef RESPONSE_H_
#define RESPONSE_H_

#include "config.h"
#include "server.h"

typedef struct Response {
  const uint8_t flag1;
  const uint8_t flag2;
  const char *response;
} resp_item;

int8_t response_driver(server_t *server, int8_t control);

inline static int8_t protocol_append_checks(server_t *server) {

  if (server->resp[server->size_resp - 4] & (0 << UNBIT)) {
    System_Message("TBYTE not unsigned");
    return FAIL;
  }
  if (server->resp[server->size_resp - 3] & (0 << UNBIT)) {
    System_Message("ABYTE not unsigned");
    return FAIL;
  }
  if (server->resp[server->size_resp - 2] & (0 << UNBIT)) {
    System_Message("SBYTE not unsigned");
    return FAIL;
  }
  if (server->resp[server->size_resp - 1] != '\0') {
    System_Message("package not nullterminated.");
    return FAIL;
  }
  return SUCC;
}

#endif