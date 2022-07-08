#ifndef RESPONSER_H_
#define RESPONSER_H_

#include "../configs.h"

typedef struct Responser {
  uint8_t *protocol;
  size_t size_pack;
  char package[RBUFF];
} resp_t;

void response_driver(resp_t *response, uint8_t *state, uint16_t *error);

#endif