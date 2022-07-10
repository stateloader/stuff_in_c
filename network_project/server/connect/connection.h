#ifndef CONNECTION_H_
#define CONNECTION_H_

#include "../system/configs.h"
#include <sys/socket.h>
#include <arpa/inet.h>

#define MCONN 16

typedef struct Server {
  int32_t server_sock_desc;
  int32_t client_sock_desc;
  struct sockaddr_in server_address;
  struct sockaddr_in client_address;
  int32_t client_length;
} serv_t;

void server_create(serv_t *server, uint16_t *status, uint16_t *error);
void server_binder(serv_t *server, uint16_t *status, uint16_t *error);

void socket_listen(serv_t *server, uint16_t *status, uint16_t *error);
void socket_accept(serv_t *server, uint16_t *status, uint16_t *error);

#endif