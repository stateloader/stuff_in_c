#ifndef RESPONSE_H_
#define RESPONSE_H_

#include "configs.h"

typedef struct Response {
  int8_t status;
  int32_t size_recv;
  char resp[FBUFF];
} resp_t;

int8_t response_driver(void *message);

#endif