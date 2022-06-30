#ifndef CLIENT_H_
#define CLIENT_H_

#include "configs.h"

typedef struct Client {
  uint8_t protocol[3];
  int32_t socket_status;
  int32_t socket_client;
  int32_t size_user;
  int32_t size_pass;
  char user[SBUFF];
  char pass[SBUFF];
} client_t;

#endif