#ifndef RECEIVE_H_
#define RECEIVE_H_

#include "../configs.h"

typedef struct Receive {
  int32_t client_sock;
  uint8_t protocol[3];
  size_t size_pack;
  char package[RBUFF];
} recv_t;

void receive_driver(recv_t *receive);

#endif
