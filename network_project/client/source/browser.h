#ifndef BROSWER_H_
#define BROWSER_H_

#include "controller.h"

#define _MAIN 0
#define _MESG 1
#define _DVCE 2
#define _DLED 3
#define _INIT 4
#define _EXIT 5

int8_t browse_driver(uint8_t *protocol);

inline static int8_t command_driver_check(uint8_t *protocol) {

  int8_t match = 0;
  for (int8_t i = 0; i < 7; i++)
    match += (protocol[TBYTE] & (1 << i)) ? 1 : 0;
  if (match == 0) {
    System_Message("Bye Bye!");
    return EXIT;
  }
  return SUCC;
}
#endif
