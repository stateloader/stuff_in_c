#ifndef COMMAND_H_
#define COMMAND_H_

#include <stddef.h>
#include <stdint.h>
#include "utils.h"

#define START 0
#define FETCH 1
#define STEER 2
#define LEAVE 3

int command_driver(char *command);

#endif
