#ifndef SOCKET_H_
#define SOCKET_H_

#include "configs.h"
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAX_CLIENT 16

void socket_create(int *server_socket);
void socket_bind(int server_socket, struct sockaddr_in *server_address, char *address, int port);
void socket_listen(int server_socket);
void socket_accept(int server_socket, int *client_socket, struct sockaddr_in *client_address);

#endif
