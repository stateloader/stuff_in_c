#ifndef SOCKET_H_
#define SOCKET_H_

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>

#define MAX_CLIENT 16

void socket_create(int *server_socket);
void socket_bind(int server_socket, struct sockaddr_in *server_address, char *address, int port);
void socket_listen(int server_socket);
void socket_accept(int server_socket, int *client_socket, struct sockaddr_in *client_address);

#endif
