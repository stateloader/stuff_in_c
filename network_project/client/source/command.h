#ifndef COMMAND_H_
#define COMMAND_H_

#include "config.h"
#include "client.h"

#define CMAIN 0
#define CMESG 1
#define CDVCE 2
#define CDLED 3
#define CINIT 4
#define CEXIT 5

int8_t command_driver(client_t *client);

#endif
