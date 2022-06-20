#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <string.h>
#include "configs.h"

typedef struct Message {
  uint8_t status;
  int32_t size_user;
  int32_t size_topc;
  int32_t size_mesg;
  char datm[TBUFF];
  char user[SBUFF];
  char topc[SBUFF];
  char mesg[SBUFF];
} mesg_t;

int8_t message_driver(mesg_t *message);
/*
inline static int8_t message_driver_check(mesg_t *message) {

  if (message->size_mesg < 1) {
    System_Message("something went south while scanning message");
    return KILL;
  } else if (message->size_topc < 1) {
    System_Message("something went south while scanning topic");
    return KILL;
  } else {
    return SUCC;
  }
}
*/
#endif