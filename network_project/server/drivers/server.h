#ifndef SERVER_H_
#define SERVER_H_

#include "sconfig.h"
#include "reader.h"
#include "writer.h"

//----------------------------------------------------------------------------------------------------------------------*/

typedef struct Session {
  int32_t sock_clnt;
  int32_t sock_serv;
} sess_t;

typedef struct Server {
  int8_t status;
  int32_t size_recv;
  int32_t size_resp;
  char recv[FBUFF];
  char resp[FBUFF];
  sess_t session;
} server_t;

#endif