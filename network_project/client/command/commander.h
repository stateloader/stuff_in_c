#ifndef COMMANDER_H_
#define COMMANDER_H_

#include "../configs.h"

#define CMAIN 0   // Command Main
#define CMESG 1   // Command Message
#define CDVCE 2   // Command Device
#define CDLED 3   // Command Device Led
#define CHELP 4   // Command Help
#define CINIT 5   // Command Init
#define CEXIT 6   // Command Exit

typedef struct CommandItem {
  const uint8_t this_state;
  const uint8_t next_state;
  const char *cmnd;
} cmnd_item;

typedef struct commander {
  uint8_t protocol[3];
} cmnd_t;

void command_driver(cmnd_t *command, uint8_t *state, uint16_t *error);

#endif
