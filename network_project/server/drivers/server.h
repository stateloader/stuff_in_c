#ifndef SERVER_H_
#define SERVER_H_

#include "controller.h"

typedef struct Connection {
  int8_t status;
  int32_t sock_clnt;
  int32_t sock_serv;
} conn_t;

typedef struct Server {
  uint8_t session;
  uint8_t protocol[3];
  int32_t size_pack;
  int32_t size_resp;
  char pack[SBUFF];
  char resp[SBUFF];
  FILE *dbfile;
  conn_t conn;
} server_t;

#endif