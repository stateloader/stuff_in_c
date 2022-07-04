#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "config.h"
#include "request.h"

typedef struct Message {
  int32_t size_user;
  int32_t size_topc;
  int32_t size_mesg;
  char datm[TBUFF];
  char user[SBUFF];
  char topc[SBUFF];
  char mesg[SBUFF];
} mesg_t;

int8_t message_driver(rqst_t *request);

#endif