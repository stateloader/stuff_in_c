/*------------------------------------------------------------------------------------------------------------------------
                                                                                                               CLIENT MAIN
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/
#include "source/configs.h"
#include "source/scanner.h"
#include "source/client.h"


static conn_t socket_setup(char *address, int32_t port) {
  Render_Header("CONNECTION", "connecting to server");
  
  conn_t conn = {.status = 1};

  conn.socket_client = socket_create();
  conn.status = socket_connect(conn.socket_client, address, port);
  conn.size_user = scan_driver(conn.user, SBUFF, "username");
  return conn;
}

int main(void) {

  conn_t conn = socket_setup("127.0.0.1", 90190);

  client_t client = {.status = 1,.conn = &conn};
  
  client_driver(&client);
  
  exit(EXIT_SUCCESS);
}