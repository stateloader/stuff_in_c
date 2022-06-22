/*------------------------------------------------------------------------------------------------------------------------
                                                                                                               CLIENT MAIN
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/
#include <stdlib.h>
#include "drivers/scanner.h"
#include "drivers/client.h"
#include "drivers/socket.h"

static const char *GENERAL = \
  "Jacke Packe CLIENT\n\n"
  "Lorem ipsum dolor sit amet, consectetur adipiscing elit.\n";

static conn_t socket_setup(char *address, int32_t port) {
  Render_Header("USERNAME", "Enter a username adreess");
  
  conn_t conn = {.status = 1};
  conn.socket_client = socket_create();
  conn.status = socket_connect(conn.socket_client, address, port);
  conn.size_user = scan_driver(conn.user, SBUFF, "username");
  return conn;
}

int main(void) {
  Render_Header("CLIENT", GENERAL);
  conn_t conn = socket_setup("127.0.0.1", 90190);            // address, port

  client_t client = {.status = 1,.conn = &conn};
  client_driver(&client);

  exit(EXIT_SUCCESS);
}