#ifndef REQUEST_H_
#define REQUEST_H_

#define INIT_MESG 0
#define INIT_DVCE 1

#include "controller.h"

typedef struct Request {
  int32_t socket;
  uint8_t *protocol;
  int32_t size_send;
  int32_t size_user;
  int32_t size_pack;
  char user[SBUFF];
  char pack[SBUFF];
} rqst_t;

typedef int8_t (*rqst_func)(rqst_t *request);

typedef struct RequestItem {
  const uint8_t task;
  rqst_func func;
} rqst_item;

int8_t request_driver(rqst_t *request);

#endif