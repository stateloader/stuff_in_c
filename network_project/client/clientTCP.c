#include <stdlib.h>
#include "connect/connection.h"
#include "configs.h"
#include "cdriver.h"

int main(void) {
  Render_Header("CLIENT", "Client ipsum dolor sit amet, consectetur adipiscing elit");

  dver_t driver = {.state = 0x00};
  clnt_t client = {.sock_desc = 0};
  client_connect(&client);

  driver.client = client;
  client_driver(&driver);
  exit(EXIT_SUCCESS);
}
