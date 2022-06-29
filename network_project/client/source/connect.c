#include "scanner.h"
#include "connect.h"

client_t connect_driver(char *address, int32_t port) {
  Render_Header("CONNECT   ", "Connecting to server");
  
  client_t client = {0};
  client.socket_client = socket_create();
  client.socket_status = socket_connect(client.socket_client, address, port);

  printf()

  client.size_user = scan_driver(client.user, SBUFF, "username");
  return client;
}