#ifndef CONNECT_H
#define CONNECT_H

#include "configs.h"
#include "client.h"

int8_t connect_driver(client_t *client, char *address, int32_t port);

#endif