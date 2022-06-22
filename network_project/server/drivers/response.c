/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                  RESPONSE
--------------------------------------------------------------------------------------------------------------------------
info fasda
------------------------------------------------------------------------------------------------------------------------*/

#include "configs.h"
#include "sstring.h"
#include "socket.h"
#include "response.h"

static char *response = "Hej pa andra sidan.\n";

int8_t response_driver(server_t *server) {

  send(server->session.sock_clnt, response, string_size(response, FBUFF), 0);
  return SUCC;
}