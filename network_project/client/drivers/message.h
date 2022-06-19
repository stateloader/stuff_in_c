#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "configs.h"

typedef struct Message {
  uint8_t status;
} mesg_t;

int8_t mesg_driver(void *message);

#endif