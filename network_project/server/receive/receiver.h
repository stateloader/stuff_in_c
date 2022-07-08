#ifndef RECEIVER_H_
#define RECEIVER_H_

#include "../configs.h"

typedef struct Receiver {
  uint8_t *protocol;
  int32_t client_sock_desc;
  size_t size_pack;
  char package[RBUFF];
} recv_t;

void receive_driver(recv_t *receive, uint16_t *state, uint16_t *error);

#endif