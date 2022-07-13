#ifndef CONNECTION_H_
#define CONNECTION_H_

#include "../system/configs.h"
#include <sys/socket.h>
#include <arpa/inet.h>

typedef struct Client {
  int32_t sock_desc, conn_stat;
  struct sockaddr_in server_address;
  size_t size_user;
  char username[SBUFF];
} clnt_t;

void client_connect(clnt_t *client, const char *address, const char *port);

#endif
