#ifndef COMMAND_H_
#define COMMAND_H_

#include "utils.h"

#define START 0
#define FETCH 1
#define STEER 2
#define LEAVE 3
size_t command_driver(char *command, uint8_t *state);

#endif
