#ifndef RECIEVE_H_
#define RECIEVE_H_

#include "configs.h"

typedef struct Recieve {
  uint8_t status;
  int32_t size_recv;
  char resv[FBUFF];
} recv_t;

int8_t recv_driver(void *message);

#endif