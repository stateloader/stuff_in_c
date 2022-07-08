#include <stdlib.h>
#include "connect/connection.h"
#include "controller.h"

int main(void) {
  Render_Header("Server", "Client ipsum dolor sit amet, consectetur adipiscing elit");

  cont_t control = {.status = 0x00};
  serv_t server = {.client_sock_desc = 0};

  server_create(&server, &control.status, &control.error);
  if (control.status & (1 << ERROR))
    exit(EXIT_FAILURE);

  server_binder(&server, &control.status, &control.error);
  if (control.status & (1 << ERROR))
    exit(EXIT_FAILURE);

  while (control.status & (1 << ALIVE))
    control_driver(&control, &server);
  
  exit(EXIT_SUCCESS);
}
