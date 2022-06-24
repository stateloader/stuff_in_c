#ifndef REQUEST_H_
#define REQUEST_H_

#define INIT_MESG 0
#define INIT_DVCE 1

#include "configs.h"

typedef struct Request {
  int8_t status;
  uint8_t protocol[3];
  int32_t size_user;
  int32_t size_rqst;
  char user[SBUFF];
  char rqst[SBUFF];
} rqst_t;

typedef void (*rqst_func)(rqst_t *request);

typedef struct RequestItem {
  const uint8_t task;
  rqst_func func;
} rqst_item;


void request_driver(rqst_t *request);

#endif