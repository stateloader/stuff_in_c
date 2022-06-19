/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                    CLIENT
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/
#include <stdlib.h>
#include "drivers/client.h"
#include "socket.h"

static const char *GENERAL = \
  "Jacke Packe CLIENT\n\n"
  "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore.\n"\
  "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore.\n"\
  "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore.\n";

int main(void) {
  Render_Header("CLIENT", GENERAL);

  meta_t meta = {.status = 1};
  client_t client = {.status = 1};  

  client.meta = &meta;

  // connections osv

  client_driver(&client);

  exit(EXIT_SUCCESS);
}