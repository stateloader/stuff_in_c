#ifndef SERVER_H_
#define SERVER_H_

#include "config.h"

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
  int32_t size_send;
  char pack[SBUFF];
  char resp[FBUFF];
  FILE *dbfile;
  conn_t conn;
} server_t;

#endif