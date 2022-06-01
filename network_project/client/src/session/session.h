#ifndef SESSION_H_
#define SESSION_H_

#include "../scan/scan.h"
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

typedef struct Session {
  int socket_desc;
  struct sockaddr_in server_addr;
} sess_t;

sess_t session_setup(char *address, int port);

#endif
