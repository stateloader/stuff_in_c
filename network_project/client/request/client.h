#ifndef CLIENT_H_
#define CLIENT_H_

#include <stdint.h>
#include "command/utils/cconfig.h"

typedef struct Client  {
  uint8_t online;
  int32_t size_user, size_pass;
  int32_t size_rqst, size_resp;
  char user[CBUFF];
  char pass[CBUFF];
  char rqst[CBUFF];
  char resp[CBUFF];
  char cmnd[CBUFF];
} client_t;

#endif