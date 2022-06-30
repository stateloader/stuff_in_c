#include "cstring.h"
#include "scanner.h"
#include "connect.h"

static int8_t connect_setup(client_t *client, char *address, int32_t port) {
  Render_Header("CONNECT   ", "Connecting to server");

  client->socket_client = socket_create();
  client->socket_status = socket_connect(client->socket_client, address, port);
  return SUCC;
}

int8_t connect_driver(client_t *client, char *address, int32_t port) { 
  connect_setup(client, address, port);

  client->size_user = scan_driver(client->user, SBUFF, "username");
  return SUCC;
}