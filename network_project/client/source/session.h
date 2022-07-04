#ifndef SESSION_H_
#define SESSION_H_

#include "cstring.h"
#include "config.h"
#include "socket.h"
#include "client.h"
#include "request.h"
#include "receive.h"
#include "browser.h"

typedef enum SessionRoutine {
  ROUT_CONF, ROUT_RQST, ROUT_SEND,
  ROUT_RESP, ROUT_RECV, ROUT_FRWD,
  ROUT_DONE
} rout_t;

int8_t session_driver(client_t *client);

inline static int8_t routine_config_check(rqst_t *request, recv_t *receive) {

  for (int8_t i = 0; i < 3; i++) {
    if (request->protocol[i] != receive->protocol[i]) {
      System_Message("request and recieve different protocol values");
      return FAIL;
    }
  } if (request->size_user != receive->size_user) {
    System_Message("request and recieve different username balues");
    return FAIL;
  } else if (request->socket != receive->socket){
    System_Message("request and recieve different socket values");
    return FAIL;
  }
  return SUCC;
}
inline static void free_session_memory(recv_t *receive) {

  if (receive->table_mesg) free(receive->table_mesg);
  if (receive->table_dvce) free(receive->table_dvce);

}
#endif