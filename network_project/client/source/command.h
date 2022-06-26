#ifndef COMMAND_H_
#define COMMAND_H_

#include "configs.h"

#define _MDEF 0x80;

#define _MAIN 0
#define _MESG 1
#define _DVCE 2
#define _EXIT 3

int8_t command_driver(uint8_t *rqst_proto, uint8_t *recv_proto);

static inline int8_t check_exit(uint8_t protocol) {
  uint8_t match = 0;
  for (uint8_t i = 0; i < 7; i++)
    match += (protocol & (1 << i));
  if (!match) {
    System_Message("Bye bye!");
    return QUIT;
  }
  return SUCC;
}

#endif
