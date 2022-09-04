#ifndef RESPONSE__H_
#define RESPONSE__H_

#include "../configs.h"

typedef struct Response {
  int32_t client_sock;
  uint8_t *protocol;
  size_t size_recv;
  size_t size_resp;
  char *received;
  char response[RBUFF];
} resp_t;

void response_driver(resp_t *response);

#endif
