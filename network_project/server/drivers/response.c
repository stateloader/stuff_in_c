#include <string.h>
#include "socket.h"
#include "response.h"

const char *response = "hej dar borta";

void response_driver(server_t *server) {
  System_Message("inside respond_driver");
  send(server->conn.sock_clnt, response, strlen(response), 0);
}
