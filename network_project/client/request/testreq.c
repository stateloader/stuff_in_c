#include <stdio.h>
#include <stdlib.h>
#include "command/utils/cstring.h"
#include "command/utils/cconfig.h"
#include "client.h"
#include "request.h"

static const char *GENERAL = \
  "Jacke Packe Koda Satan\n\n"
  "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore.\n"\
  "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore.\n"\
  "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore.\n";

int main(void) {
  
  Print_Header("CLIENT", GENERAL);
  
  client_t client = {.online = 0};

  if (request_driver(&client) == FLEE)
    exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);
}