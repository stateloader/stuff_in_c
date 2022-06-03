#ifndef CONNECTION_H_
#define CONNECTION_H_

#include "utils.h"

#define SOCK 0
#define CONN 1
#define CMND 2
#define RQST 3
#define RECV 4
#define EXIT 5

typedef struct Connection {
  int socket;
  struct sockaddr_in server;
} conn_t;

conn_t setup_connection(char *address, int port, uint8_t *state);

#endif
