#ifndef SERVER_H_
#define SERVER_H_

#include "sconfig.h"

//----------------------------------------------------------------------------------------------------------------------*/

typedef struct Session {  //client
  int32_t sock_clnt;
  int32_t sock_serv;       //ner
} sess_t;                // cent_t

typedef struct Server {
  uint8_t endbyte;
  int32_t size_recv;
  int32_t size_resp;
  char recv[FBUFF];
  char resp[FBUFF];
  void *table;
  sess_t session;         // cent_t client
} server_t;

#endif