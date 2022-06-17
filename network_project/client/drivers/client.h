#ifndef CLIENT_H_
#define CLIENT_H_

#include <stdint.h>
#include "cconfig.h"

typedef struct Message {
  int32_t size_datm;
  int32_t size_topc;
  int32_t size_mesg;
  char datm[CBUFF];
  char topc[CBUFF];
  char mesg[CBUFF];
} mesg_t;

typedef struct Client  {
  uint8_t online;
  int32_t size_user;
  int32_t size_pass;
  int32_t size_rqst;
  int32_t size_resp;
  char user[CBUFF];
  char pass[CBUFF];
  char rqst[CBUFF];
  char resp[CBUFF];
  char cmnd[CBUFF];
  mesg_t mesg;
} client_t;

#endif