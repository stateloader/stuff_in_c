#ifndef CLIENT_H_
#define CLIENT_H_

#include "scan.h"
#include "connection.h"

#define WMENU 0x00
#define WREQT 0x01
#define WRESP 0x02

typedef struct User {
  char time[16];
  char name[16];
} user_t;

typedef struct Client {
  uint8_t view;
  conn_t *conn;
  user_t user;
  size_t sizereq, sizeres;
  char request[MAX_BUFFER];
  char response[MAX_BUFFER];
} cent_t;


void client_request(cent_t *client, char *message);

#endif
