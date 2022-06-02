#ifndef CLIENT_H_
#define CLIENT_H_

#include "connection.h"

typedef struct Client {
  size_t length;
  char request[MAX_BUFFER];
  char response[MAX_BUFFER];
  conn_t *conn;
} cent_t;


void client_input(cent_t *client, char *message);

#endif
