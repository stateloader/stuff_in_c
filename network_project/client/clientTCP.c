/*------------------------------------------------------------------------------------------------------------------------
                                                                                                               CLIENT MAIN
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/
#include "source/configs.h"
#include "source/scanner.h"
#include "source/client.h"


static client_t socket_setup(char *address, int32_t port) {
  Render_Header("CONNECTION", "connecting to server");
  
  client_t client = {0};
  client.socket_client = socket_create();
  client.socket_status = socket_connect(client.socket_client, address, port);
  client.size_user = scan_driver(client.user, SBUFF, "username");
  return client;
}

int main(void) {

  client_t client = socket_setup("127.0.0.1", 90190);  
  client_driver(&client);
  
  exit(EXIT_SUCCESS);
}