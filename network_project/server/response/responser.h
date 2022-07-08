#ifndef RESPONSER_H_
#define RESPONSER_H_

#include "../configs.h"

typedef struct Responser {
  int32_t client_sock_desc;
  uint8_t protocol[3];
  size_t size_recv;
  char received[SBUFF];
  size_t size_resp;
  char response[RBUFF];
} resp_t;

void response_driver(resp_t *response, uint16_t *state, uint16_t *error);

#endif