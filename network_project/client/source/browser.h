#ifndef BROSWER_H_
#define BROWSER_H_

#include "configs.h"

#define _CONN 0
#define _MAIN 1
#define _MESG 2
#define _DVCE 3
#define _DLED 4
#define _INIT 5
#define _EXIT 6

int8_t browse_driver(uint8_t *protocol);

inline static int8_t command_driver_check(uint8_t *protocol) {

  int8_t match = 0;
  for (int8_t i = 0; i < 7; i++)
    match += (protocol[TBYTE] & (1 << i)) ? 1 : 0;
  if (match == 0) {
    Message_Info("Bye Bye!");
    return EXIT;
  }
  return SUCC;
}
#endif
