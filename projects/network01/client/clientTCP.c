/*----------------------------------------------------------------------------------------CLIENT TCP
Main function.
--------------------------------------------------------------------------------------------------*/
#include <stdlib.h>
#include "connect/connect.h"
#include "configs.h"
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

  validate_usage(argc);

  cent_t client = client_connect(argv[1], argv[2]);

  driver_t driver = {.client = client};
  driver.state |= (1 << SCONN);
  
  client_driver(&driver);
  
  exit(EXIT_SUCCESS);
}
