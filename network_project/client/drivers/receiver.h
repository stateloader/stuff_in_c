#ifndef RECEIVER_H_
#define RECEIVER_H_

#include "configs.h"

typedef struct Receive {
  int8_t status;
  int32_t size_recv;
  char resp[FBUFF];
} recv_t;

int8_t response_driver(void *message);

#endif