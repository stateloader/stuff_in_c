#ifndef CLIENT_H_
#define CLIENT_H_

#include "scan.h"
#include "connection.h"

#define WMENU 0
#define WREQT 1
#define WRESP 2

typedef struct User {
  char time[16];
  char name[16];
} user_t;

typedef struct Client {
  uint8_t view;
  conn_t *conn;
  user_t user;
  size_t sizereq, sizeres;
  char request[MAX_BUFFER];		//reqcmnd
  char response[MAX_BUFFER];  //resmesg
} cent_t;


void client_request(cent_t *client, char *message);

#endif
