/*-----------------------------------------------------------------------------------------------------------------CONNECT
Ehh, I made something. It turned out as nothing. At the moment we're just enter a password for funzies.
------------------------------------------------------------------------------------------------------------------------*/

#include "cstring.h"
#include "connect.h"
#include "scanner.h"

 int8_t connect_driver(client_t *client, char *address, int32_t port) {
  Render_Header("CONNECT   ", "Connecting to server");

  client->conn.socket_client = socket_create();
  client->conn.socket_status = socket_connect(client->conn.socket_client, address, port);

  Render_Header("VALIDATE  ", "Enter username and password");

  client->size_user = scan_driver(client->user, "username", SBUFF);
  client->size_pass = scan_driver(client->pass, "password", SBUFF);

  return SUCC;
}