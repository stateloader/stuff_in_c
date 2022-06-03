#ifndef COMMAND_H_
#define COMMAND_H_

#include "utils.h"

#define ARRNOW 3

#define BEGIN_ENTRY 0
#define FETCH_ENTRY 1
#define STEER_ENTRY 2

typedef void (*cmnd_func)(char *command);

typedef struct {
  cmnd_func func;
} cmnd_item;

void command_driver(char *command, size_t size);

#endif
