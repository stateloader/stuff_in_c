#ifndef RECEIVE_H_
#define RECEIVE_H_

#include "configs.h"

typedef struct Receive {
  int8_t status;
  int32_t size_recv;
  char recv[FBUFF];
} recv_t;

void receive_driver(int32_t client_socket, recv_t *receive);

#endif