#ifndef REQUEST_H_
#define REQUEST_H_

#include <stdint.h>
#include "command/utils/cconfig.h"

typedef int8_t (*command_func)(char *command);

typedef struct CommandItem {
  command_func func;
} command_item;

uint32_t request_driver(char *request, char *command);
  
#endif
