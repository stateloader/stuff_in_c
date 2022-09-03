#ifndef MESSAGE__H_
#define MESSAGE__H_

#include "../configs.h"
#include "request.h"

typedef struct Message {
  size_t size_subj;
  size_t size_comm;
  char subject[SBUFF];
  char comment[SBUFF];
} mesg_t;

void message_driver(reqt_t *request);

#endif 
