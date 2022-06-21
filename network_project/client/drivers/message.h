#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <string.h>
#include "configs.h"
#include "request.h"

#define MESG_CRTE 0
#define MESG_READ 1

typedef struct Message {
  int8_t status;
  int8_t exec;
  int32_t size_user;
  int32_t size_topc;
  int32_t size_mesg;
  char datm[TBUFF];
  char user[SBUFF];
  char topc[SBUFF];
  char mesg[SBUFF];
} mesg_t;

void message_driver(rqst_t *request);

inline static int8_t message_exec_check(int8_t exec) {
  if (exec & (1 << RWBIT))
    return MESG_CRTE;
  else
    return MESG_READ;
}

inline static void message_create_checks(mesg_t *message) {
  
  if (message->size_topc < 1) {
    System_Message("something went south while writing topic.");
    message->status = 0;
  } else if (message->size_mesg < 1) {
    System_Message("something went south while writing message.");
    message->status = 0;
  }
}

#endif