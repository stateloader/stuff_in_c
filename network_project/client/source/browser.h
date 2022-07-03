#ifndef BROSWER_H_
#define BROWSER_H_

#include "controller.h"

#define BMAIN 0
#define BMESG 1
#define BDVCE 2
#define BDLED 3
#define BINIT 4
#define BEXIT 5

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
