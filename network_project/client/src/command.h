#ifndef COMMAND_H_
#define COMMAND_H_

#include "utils.h"

#define OSTART 0
#define OFETCH 1
#define OSTEER 2
#define OLEAVE 3

void command_driver(char *command, uint8_t *state);

typedef uint8_t (*option_func)(char *command, char *state);

typedef sttruct OptionItem {
  option_func func;
} option_item;

#endif
