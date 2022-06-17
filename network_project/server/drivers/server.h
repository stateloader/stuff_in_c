#ifndef SERVER_H_
#define SERVER_H_

#include "sconfig.h"
#include "reader.h"
#include "writer.h"

//----------------------------------------------------------------------------------------------------------------------*/

typedef struct Session {  //client
  int32_t sock_clnt;
  int32_t sock_serv;       //ner
} sess_t;                // cent_t

typedef struct Server {
  uint8_t endbyte;
  int8_t result;
  char recv[FBUFF];
  char resp[FBUFF];
  int32_t size_recv;
  int32_t size_resp;
  read_t reader;
  write_t writer;
  sess_t session;         // cent_t client
} server_t;

#endif