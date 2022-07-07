#ifndef SOCKET_H_
#define SOCKET_H_

#include "../configs.h"

int32_t socket_create(void);
int32_t socket_connect(int32_t client_socket, char *address, int32_t port);

#endif
