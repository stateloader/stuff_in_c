/*-------------------------------------------------------------------------------------
																																		  CONNECTION MODULE
---------------------------------------------------------------------------------------
GENERAL
---------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------*/

#ifndef CONNECTION_H_
#define CONNECTION_H_

#include "utils.h"
#include "client.h"

#define SOCK 0
#define CONN 1
#define SEND 2
#define RECV 3
#define FREQ 4
#define FRES 5

typedef struct Connection {
  uint8_t status;
  cent_t client;
  int socket;
  struct sockaddr_in server;
} conn_t;

conn_t setup_connection(char *address, int port);
void browse_session(conn_t *conn);

#endif
