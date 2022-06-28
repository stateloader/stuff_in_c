#ifndef COMMAND_H_
#define COMMAND_H_

#include "configs.h"

#define _MAIN 0
#define _MESG 1
#define _DVCE 2
#define _DLED 3
#define _EXIT 4

int8_t command_driver(uint8_t *protocol);

inline static int8_t command_driver_check(uint8_t *protocol) {

  int8_t match = 0;
  for (int8_t i = 0; i < 7; i++)
    match += (protocol[TINDX] & (1 << i)) ? 1 : 0;
  if (match == 0) {
    Message_Info("Bye Bye!");
    return EXIT;
  }
  return SUCC;
}

#endif
