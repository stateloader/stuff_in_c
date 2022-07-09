#ifndef RECEIVER_H_
#define RECEIVER_H_

#include "../system/configs.h"

typedef struct Receiver {
  int32_t client_sock_desc;
  uint8_t protocol[3];
  size_t size_pack;
  char package[RBUFF];
} recv_t;

void receive_driver(recv_t *receive, uint16_t *state, uint16_t *error);

#endif