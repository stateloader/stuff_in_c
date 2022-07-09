#ifndef RESPONDER_H_
#define RESPONDER_H_

#include "../system/configs.h"

typedef struct Responder {
  int32_t client_sock_desc;
  uint8_t protocol[3];
  size_t size_recv;
  char received[SBUFF];
  size_t size_resp;
  char response[RBUFF];
} resp_t;

void response_driver(resp_t *response, uint16_t *state, uint16_t *error);

#endif