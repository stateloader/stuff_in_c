#include <stdlib.h>
#include "connect/connection.h"
#include "system/configs.h"
#include "cdriver.h"

static void validate_usage(int argc) {

  if (argc != 3) {
    Render_Header("USAGE", "Too few argments. You must enter IP-address and port.");
    System_Message("Example: ./clientTCP 127.0.0.1 90190");
    exit(EXIT_FAILURE);
  }
  return;
}

int main(int argc, char **argv) {

  //validate_usage(argc);

  clnt_t client = {.sock_desc = 0};
  client_connect(&client, "127.0.0.1", "90190");

  dver_t driver = {.client = client};
  driver.state |= (1 << SCONN);
  
  client_driver(&driver);
  if (driver.state & (1 << ERROR))
    exit(EXIT_FAILURE);
    
  exit(EXIT_SUCCESS);
}