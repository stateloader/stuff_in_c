#ifndef CLIENT_H_
#define CLIENT_H_

#include <stdint.h>
#include "command/utils/cconfig.h"

typedef struct Client  {
  uint8_t online;
  int32_t size_user;
  int32_t size_pass;
  int32_t size_rqst;
  int32_t size_resp;
  char user[CBUFF];
  char pass[CBUFF];
  char cmnd[CBUFF];
  char rqst[CBUFF];
  char resp[CBUFF];
} client_t;

#endif