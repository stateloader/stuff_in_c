#include <stdlib.h>
#include "connect/connection.h"
#include "system/configs.h"
#include "sdriver.h"

int main(void) {
  Render_Header("Server", "Client ipsum dolor sit amet, consectetur adipiscing elit");

  dver_t driver = {.status = 0x00};
  serv_t server = {.client_sock_desc = 0};

  server_create(&server, &driver.status, &driver.error);
  if (driver.status & (1 << ERROR))
    exit(EXIT_FAILURE);

  server_binder(&server, &driver.status, &driver.error);
  if (driver.status & (1 << ERROR))
    exit(EXIT_FAILURE);

  while (driver.status & (1 << ALIVE))
    server_driver(&driver, &server);
  
  exit(EXIT_SUCCESS);
}
