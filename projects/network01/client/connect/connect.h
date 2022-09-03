#ifndef CONNECT__H_
#define CONNECT__H_

#include "../configs.h"
#include <sys/socket.h>
#include <arpa/inet.h>

typedef struct Client {
  int32_t sock_desc;
  int32_t conn_stat;
  size_t size_user;
  char username[SBUFF];
  char password[SBUFF]; // not in place atm.
  struct sockaddr_in server_address;
} cent_t;

cent_t client_connect(const char *address, const char *port);

#endif
