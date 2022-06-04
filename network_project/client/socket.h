#ifndef SOCKET_H_
#define SOCKET_H_

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

#define SOCK 0
#define CONN 1
#define CMND 2
#define RQST 3
#define RECV 4
#define EXIT 5

int socket_create(void);
int socket_connect(int client_socket, char *address, int port);
int socket_send(int client_socket, char* request, size_t request_size);
int socket_recieve(int client_socket, char* response, size_t response_size);

#endif
