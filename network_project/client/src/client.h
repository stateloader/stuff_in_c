#ifndef CLIENT_H_
#define CLIENT_H_

#include "scan.h"
#include "connection.h"

#define WFREE 0x00
#define WALLC 0x01
#define WMENU 0x02
#define WRQST 0x03
#define WRESP 0x04

typedef struct Client {
  conn_t *conn;
  uint8_t controller;
  size_t sizereq, sizeres;
  char request[MAX_BUFFER];
  char response[MAX_BUFFER];
} cent_t;

void client_request(cent_t *client, char *message);

#endif
