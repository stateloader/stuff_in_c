#ifndef COMMAND_H_
#define COMMAND_H_

#include "configs.h"

typedef struct CmndItem {
  const char *cmnd;
  const uint8_t byte;
} cmnd_item;

typedef struct Command {
  uint8_t status;
  uint8_t main_byte;
  uint8_t late_byte;
  uint32_t size_cmnd;
  char command[SBUFF];
} cmnd_t;

int8_t command_driver(cmnd_t *cmnd);

#endif
