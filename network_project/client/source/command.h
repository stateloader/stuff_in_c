#ifndef COMMAND_H_
#define COMMAND_H_

#include "configs.h"

#define _CONN 0
#define _LOGN 1
#define _SIGN 2
#define _MAIN 3
#define _MESG 4
#define _DVCE 5
#define _DLED 6
#define _DONE 7
#define _EXIT 8

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
