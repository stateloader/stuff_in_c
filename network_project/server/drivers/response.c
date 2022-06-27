#include <string.h>
#include "socket.h"
#include "response.h"

static char *temp = "hello on the other siiiiiiide";

int8_t response_driver(server_t *server) {
  System_Message("inside respond_driver");
  send(server->conn.sock_clnt, temp, strlen(temp), 0);
  return SUCC;
}
