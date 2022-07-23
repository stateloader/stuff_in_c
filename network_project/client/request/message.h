#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "../system/configs.h"
#include "requester.h"

#define MESGR 0 //  Message Pull
#define MESGW 1 //  Message Push

typedef struct Message {
  size_t size_subj;
  size_t size_comm;
  char subject[SBUFF];
  char comment[SBUFF];
} mesg_t;

void message_driver(reqt_t *request, uint8_t *state, uint16_t *error);

#endif 