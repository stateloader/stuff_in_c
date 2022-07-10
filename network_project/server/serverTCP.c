#include <stdlib.h>
#include "connect/connection.h"
#include "system/configs.h"
#include "sdriver.h"
/*

  dver_t driver = {.state = 0x00};
  clnt_t client = {.sock_desc = 0};
  client_connect(&client);

  driver.client = client;
  driver.state |= (1 << SCONN);
*/

int main(void) {
  Render_Header("SERVER", "SERVER ipsum dolor sit amet, consectetur adipiscing elit");

  dver_t driver = {.status = 0x00};
  serv_t server = {.client_sock_desc = 0};

  server_create(&server);
  server_binder(&server);

  driver.server = server;
  driver.status |= (1 << SCONN);


  while (driver.status & (1 << SCONN))
    server_driver(&driver);
  
  exit(EXIT_SUCCESS);
}
