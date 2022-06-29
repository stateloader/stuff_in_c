#ifndef CLIENT_H_
#define CLIENT_H_

#include "configs.h"
#include "socket.h"
#include "request.h"
#include "receive.h"
#include "command.h"

typedef enum ClientRoutine {
  ROUT_CMND, ROUT_RQST, ROUT_SEND,
  ROUT_RESP, ROUT_RECV, ROUT_FRWD,
  ROUT_DONE
} rout_t;

typedef struct Client {
  uint8_t protocol[3];
  int32_t socket_client;
  int32_t socket_status;
  int32_t size_user;
  char user[SBUFF];
} client_t;

int8_t client_driver(client_t *client);

#endif