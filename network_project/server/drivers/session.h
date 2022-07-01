#ifndef SESSION_H_
#define SESSION_H_

#include "configs.h"
#include "server.h"

typedef enum ServerRoutine {
  ROUT_ACCP, ROUT_RECV, ROUT_RESP, ROUT_RSET
} rout_t;


int8_t session_driver(server_t *server, char *address, int32_t port);

#endif