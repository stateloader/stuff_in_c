#ifndef CLIENT_H_
#define CLIENT_H_

#include "configs.h"
#include "socket.h"
#include "request.h"
#include "receive.h"
#include "command.h"

typedef enum ClientRoutine {
  ROUT_CONF, ROUT_RQST, ROUT_SEND,
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

inline static int8_t routine_config_check(rqst_t *request, recv_t *receive) {

  for (int8_t i = 0; i < 3; i++) {
    if (request->protocol[i] != receive->protocol[i]) {
      Message_Info("request and recieve different protocol values");
      return FAIL;
    }
  } if (request->size_user != receive->size_user) {
    Message_Info("request and recieve different username balues");
    return FAIL;
  } else if (request->socket != receive->socket){
    Message_Info("request and recieve different socket values");
    return FAIL;
  }
  return SUCC;
}

#endif