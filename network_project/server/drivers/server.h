#ifndef SERVER_H_
#define SERVER_H_

#include "sconfig.h"

//----------------------------------------------------------------------------------------------------------------------*/

typedef struct Session {
  int32_t sock_clnt;
  int32_t sock_serv;
} sess_t;

typedef struct Server {
  uint8_t endbyte;
  uint8_t dborder;
  int32_t size_recv;
  int32_t size_resp;
  char recv[FBUFF];
  char resp[FBUFF];
  void *table;
  sess_t session;
} server_t;

#endif