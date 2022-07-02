#ifndef RESPONSE_H_
#define RESPONSE_H_

#include "controller.h"
#include "server.h"

typedef struct Response {
  const uint8_t flag1;
  const uint8_t flag2;
  const char *response;
} resp_item;

int8_t response_driver(server_t *server, int8_t control);

#endif