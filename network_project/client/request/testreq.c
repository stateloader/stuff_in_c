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
  
  Render_Header("CLIENT", GENERAL);
  
  int8_t result = 0;
  client_t client = {.online = 0};
  
  result = request_driver(&client);
  if (result == FLEE)
    exit(EXIT_FAILURE);

  uint8_t reqmask = client.rqst[client.size_rqst - 2];
  PrintByte(reqmask);
  exit(EXIT_SUCCESS);
}