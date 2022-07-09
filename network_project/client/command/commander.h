#ifndef COMMANDER_H_
#define COMMANDER_H_

#include "../system/configs.h"

#define CMAIN 0   // command main
#define CMESG 1   // command message
#define CDVCE 2   // command device
#define CDLED 3   // command device Led
#define CHELP 4   // command help
#define CINIT 5   // command init
#define CEXIT 6   // command exit

typedef struct CommandItem {
  const uint8_t this_state;
  const uint8_t next_state;
  const char *cmnd;
} cmnd_item;

typedef struct commander {
  uint8_t state;
  uint8_t protocol[3];
} cmnd_t;

void command_driver(cmnd_t *command);

#endif
