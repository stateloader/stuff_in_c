#ifndef RESPONSE_H_
#define RESPONSE_H_

#include "configs.h"

typedef struct Response {
  uint8_t status;
  int32_t size_recv;
  char resv[FBUFF];
} resp_t;

int8_t response_driver(void *message);

#endif