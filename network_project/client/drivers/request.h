#ifndef REQUEST_H_
#define REQUEST_H_

#include "configs.h"

typedef struct Request {
  uint8_t status;
  uint8_t rqst_byte;
  uint32_t size_user;
  uint32_t size_rqst;
  char user[SBUFF];
  char rqst[SBUFF];
} rqst_t;

int8_t request_driver(rqst_t *request);

#endif