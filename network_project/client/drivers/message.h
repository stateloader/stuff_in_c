#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "configs.h"

typedef struct Message {
  uint8_t status;
  int32_t size_user;
  int32_t size_topc;
  int32_t size_mesg;
  char user[SBUFF];
  char datm[TBUFF];
  char topc[SBUFF];
  char mesg[SBUFF];
} mesg_t;

int8_t message_driver(mesg_t *message);

#endif