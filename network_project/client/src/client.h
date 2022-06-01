#ifndef CLIENT_H_
#define CLIENT_H_

#include "session/session.h"

#define USER_NAME 16

/*
typedef struct Session {
18   uint8_t status;
19   int socket;
20   struct sockaddr_in server;
21 } sess_t;
*/

typedef struct Client {
  char username[USER_NAME];
  char command[MAX_BUFFER];
  char comment[MAX_BUFFER];
  sess_t *session;
} cent_t;

#endif
