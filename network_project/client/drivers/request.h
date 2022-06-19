#ifndef REQUEST_H_
#define REQUEST_H_

#include "configs.h"

typedef struct Request {
  uint8_t status;
  uint32_t size_rqst;
  uint8_t request[SBUFF];
} rqst_t;

int8_t request_driver(rqst_t *request);

#endif