/*------------------------------------------------------------------------------------SERVER DRIVER

-------------------------------------------------------------------------------------------------*/
#include "connect/connect.h"
#include "configs.h"
#include "sdriver.h"

static void validate_usage(int argc) {

  if (argc != 3) {
    Render_Header("USAGE", "Too few argments. You must enter IP-address and port.");
    System_Message("Example: ./serverTCP 127.0.0.1 90190");
    exit(EXIT_FAILURE);
  }
  return;
}

int main(int argc, char **argv) {
  Render_Header("SERVER", "A noble piece of software in which absolute nothing can go wrong");

  validate_usage(argc);

  driver_t driver = {.status = 0x00};
  serv_t server = {.client_sock_desc = 0};

  server_connect(&server, argv[1], argv[2]);

  driver.server = server;
  driver.status |= (1 << SCONN);

  while (driver.status & (1 << SCONN)) {
    socket_listen(&driver.server);
    socket_accept(&driver.server);
    server_driver(&driver);
  }
  exit(EXIT_SUCCESS);
}
