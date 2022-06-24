#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <string.h>
#include "configs.h"
#include "request.h"

typedef struct Message {
  int8_t status;
  int32_t size_user;
  int32_t size_topc;
  int32_t size_mesg;
  char datm[TBUFF];
  char user[SBUFF];
  char topc[SBUFF];
  char mesg[SBUFF];
} mesg_t;

void message_driver(rqst_t *request);

#endif