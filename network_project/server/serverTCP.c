#include <stdlib.h>
#include "connect/connection.h"
#include "system/configs.h"
#include "sdriver.h"


int main(void) {
  Render_Header("SERVER", "A noble piece of software in which absolute nothing can go wrong");

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
