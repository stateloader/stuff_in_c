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
  uint8_t status;
  uint8_t protocol[3];
  conn_t *conn;
  rqst_t *rqst;
  recv_t *recv;
} client_t;

int8_t client_driver(client_t *client);

static inline int8_t check_prcl(rqst_t *request) {
  uint8_t match = 0;
  for (uint8_t i = 0; i < 7; i++)
    match += (request->protocol[TINDX] & (1 << i));
  if (!match) {
    System_Message("bye!");
    return FAIL;
  }
  return SUCC;
}

static inline int8_t check_send(rqst_t *request) {
  if (request->size_send != request->size_rqst) {
    System_Message("failed to send request");
    return FAIL;
  }
  return SUCC;
}

static inline int8_t check_recv(recv_t *receive) {
  if (receive->size_recv == FBUFF) {
    System_Message("database-buffer to small, fix");
    return FAIL;
  }
  return SUCC;
}

#endif