#ifndef CLIENT_H_
#define CLIENT_H_

#include "configs.h"
#include "request.h"
#include "command.h"
#include "recieve.h"

typedef struct ClMeta {
  uint8_t status;
  int32_t socket_client;
  int32_t size_user;
  char username[SBUFF];
} meta_t;

typedef struct Client {
  uint8_t status;
  meta_t *meta;
  cmnd_t *command;
  rqst_t *request;
  recv_t *recieve;
} client_t;

int8_t client_driver(client_t *client);

#endif