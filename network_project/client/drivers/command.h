#ifndef COMMAND_H_
#define COMMAND_H_

#include "configs.h"

typedef struct Command {
  uint8_t status;
  uint8_t task_byte;
  uint8_t exec_byte;
  uint8_t rqst_byte;
  uint32_t size_cmnd;
  char command[SBUFF];
} cmnd_t;

int8_t command_driver(cmnd_t *cmnd);

inline static int8_t command_driver_check(cmnd_t *cmnd) {
  uint8_t sets = 0;
  for (int8_t i = 0; i < 8; i++)
    sets += (cmnd->exec_byte & (1 << i));
  if (!sets) {
    System_Message("Good bye");
    return QUIT;
  }
  return SUCC;
}

#endif
