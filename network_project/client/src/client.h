#ifndef CLIENT_H_
#define CLIENT_H_

#include "scan.h"
#include "connection.h"

#define WFREE 0
#define WALLC 1
#define WMENU 2
#define WRQST 3
#define WRESP 4

typedef struct Client {
  conn_t conn;
  uint8_t controller;
  size_t sizereq, sizeres;
  char request[MAX_BUFFER];
  char response[MAX_BUFFER];
} cent_t;

void client_session(cent_t *client);

#endif
