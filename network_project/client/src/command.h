#ifndef COMMAND_H_
#define COMMAND_H_

#include "utils.h"

#define START 0
#define FETCH 1
#define STEER 2
void command_driver(char *command, uint8_t *state);
/*
typedef uint8_t (*option_func)(char *command, char *state);

typedef sttruct OptionItem {
  option_func func;
} option_item;
*/
#endif
