#ifndef COMMAND_H_
#define COMMAND_H_

#include "configs.h"

#define _MAIN 0
#define _MESG 1
#define _DVCE 2
#define _EXIT 3

typedef struct Command {
  uint8_t status;
  int8_t protocol[3];
} cmnd_t;

int8_t command_driver(cmnd_t *cmnd);

#endif
