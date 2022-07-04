#ifndef CONNECT_H
#define CONNECT_H

#include "config.h"
#include "session.h"

int8_t connect_driver(client_t *client, char *address, int32_t port);

#endif