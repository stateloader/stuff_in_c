#ifndef CLIENT_H_
#define CLIENT_H_

#include "configs.h"
#include "socket.h"
#include "request.h"
#include "receive.h"
#include "command.h"

typedef struct Connection {
  int8_t status;
  int32_t socket_client;
  int32_t size_user;
  char user[SBUFF];
} conn_t;

typedef struct Client {
  uint8_t protocol[3];
  conn_t *conn;
} client_t;

int8_t client_driver(client_t *client);

static inline int8_t check_send(rqst_t *request) {
  if (request->size_send != request->size_rqst) {
    System_Message("failed to send request");
    return FAIL;
  }
  return SUCC;
}

#endif