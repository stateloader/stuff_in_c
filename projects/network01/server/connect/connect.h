#ifndef CONNECT__H_
#define CONNECT__H_

#include "../configs.h"
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

void server_connect(serv_t *client, const char *ADDRESS, const char *PORT_STR);
void socket_listen(serv_t *server);
void socket_accept(serv_t *server);

#endif
