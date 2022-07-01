#ifndef SOCKET_H_
#define SOCKET_H_

#include "controller.h"
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAX_CLIENT 16

int8_t socket_create(int *server_socket);
int8_t socket_binder(int server_socket, struct sockaddr_in *server_address, char *address, int port);
int8_t socket_listen(int server_socket);
int8_t socket_accept(int server_socket, int *client_socket, struct sockaddr_in *client_address);

#endif
