#include <string.h>
#include "socket.h"
#include "response.h"

void response_driver(server_t *server) {
  System_Message("inside respond_driver");
  send(server->conn.sock_clnt, server->resp, server->size_resp, 0);
}
