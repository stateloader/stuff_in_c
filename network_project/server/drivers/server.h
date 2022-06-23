#ifndef SERVER_H_
#define SERVER_H_

#include "configs.h"
#include "socket.h"

typedef struct Connection {
  int8_t status;
  int32_t sock_clnt;
  int32_t sock_serv;
} conn_t;

typedef struct Server {
  int8_t status;
  uint8_t protocol[3];
  int32_t size_recv;
  int32_t size_resp;
  char recv[SBUFF];
  char resp[SBUFF];
  FILE *dbfile;
  conn_t conn;
} server_t;

#endif