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
  conn_t *conn;
  rqst_t *request;
  recv_t *receive;
} client_t;

void client_driver(client_t *client);

#endif