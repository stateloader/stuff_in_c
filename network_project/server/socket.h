#ifndef SOCKET_H_
#define SOCKET_H_

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>

#define SOCK 0
#define CONN 1
#define CMND 2
#define RQST 3
#define RECV 4
#define EXIT 5

int socket_create(void);
int socket_bind(int client_socket, char *address, int port);
//int socket_accept(int server_socket, struct sockaddr_in client_address);
//int socket_recieve(int client_socket, char *response, int response_size);
//int socket_send(int client_socket, char *request, int request_size);
//void socket_close(int client_socket);

#endif