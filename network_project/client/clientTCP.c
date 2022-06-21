/*------------------------------------------------------------------------------------------------------------------------
                                                                                                               CLIENT MAIN
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/
#include <stdlib.h>
#include "drivers/scanner.h"
#include "drivers/client.h"
#include "drivers/socket.h"

static const char *GENERAL = \
  "Jacke Packe CLIENT\n\n"
  "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore.\n"\
  "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore.\n"\
  "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore.\n";


static meta_t create_meta(void) {
  Render_Header("USERNAME", "Tell who you are!");
  meta_t meta = {.status = 1};
  meta.size_user = scan_driver(meta.user, SBUFF, "username");
  return meta;
}

static client_t create_client(void) {
  client_t client = {.status = 1};
  return client;
}

int main(void) {
  Render_Header("CLIENT", GENERAL);

  meta_t meta = create_meta();
  client_t client = create_client();

  client.meta = &meta;

  client_driver(&client);

  exit(EXIT_SUCCESS);
}