#ifndef CONNECTION_H_
#define CONNECTION_H_

#include "utils.h"

#define SOCK 0
#define CONN 1
#define CMND 2
#define RQST 3
#define RESP 4
#define EXIT 5

typedef struct Connection {
  uint8_t status;
  int socket;
  struct sockaddr_in server;
} conn_t;

conn_t setup_connection(char *address, int port);

#endif
