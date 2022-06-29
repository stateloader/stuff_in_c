#ifndef CONNECT_H
#define CONNECT_H

#include "configs.h"
#include "client.h"

client_t connect_driver(char *address, int32_t port);

#endif