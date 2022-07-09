#include <stdlib.h>
#include "command/scanner.h"
#include "configs.h"
#include "cdriver.h"

int main(void) {
  Render_Header("CLIENT", "Client ipsum dolor sit amet, consectetur adipiscing elit");

  dver_t driver = {.state = 0x00};
  driver.state |= (1 << ALIVE);

  Render_Header("VALIDATE  ", "Enter username and password");
  driver.size_user = scan_driver(driver.username, "username", SBUFF);
  driver.size_user = scan_driver(driver.password, "password", SBUFF);
//For now, no password handeling at place at all though :)

  while (driver.state & (1 << ALIVE))
    client_driver(&driver);
  exit(EXIT_SUCCESS);
}
