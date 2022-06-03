#ifndef CLIENT_H_
#define CLIENT_H_

#include "connection.h"

typedef struct Client {
  uint8_t state;
  conn_t conn;
  size_t length;
  char request[MAX_BUFFER];    // used for both commands and requests
  char command[MAX_BUFFER];
  char response[MAX_BUFFER];
} cent_t;

void client_session(cent_t *client);

#endif
