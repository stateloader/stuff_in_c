#ifndef REQUEST_H_
#define REQUEST_H_

#include <stdint.h>
#include "reqdrivers/utils/cconfig.h"
#include "client.h"

typedef int8_t (*command_func)(client_t *client);

typedef struct CommandItem {
  command_func func;
} command_item;

int8_t request_driver(client_t *client);
  
#endif
