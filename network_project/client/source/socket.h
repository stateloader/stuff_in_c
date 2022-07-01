#ifndef SOCKET_H_
#define SOCKET_H_

#include "controller.h"
#include <sys/socket.h>
#include <arpa/inet.h>

int32_t socket_create(void);
int32_t socket_connect(int32_t client_socket, char *address, int32_t port);
int32_t socket_send(int32_t client_socket, char* request, int32_t request_size);
int32_t socket_recieve(int32_t client_socket, char* response, int32_t response_size);

#endif
