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

typedef struct Commander {
  uint8_t menu_state;
  uint8_t *protocol;
  size_t size_cmnd;
  char cmnd[SBUFF];
} cmnd_t;

void command_driver(uint8_t *protocol);

#endif
