#ifndef COMMAND_H_
#define COMMAND_H_

#include "config.h"
#include "client.h"

#define CMAIN 0
#define CMESG 1
#define CDVCE 2
#define CDLED 3
#define CHELP 4
#define CINIT 5
#define CEXIT 6

int8_t command_driver(client_t *client);

#endif
