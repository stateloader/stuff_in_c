/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                    SERVER
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/

#include "drivers/session.h"

int main(void) {
  Render_Header("SERVER", "Server ipsum dolor sit amet, consectetur adipiscing elit");

  server_t server = {.session = 0x80};
  session_driver(&server, "127.0.0.1", 90190);
  exit(EXIT_SUCCESS);
}