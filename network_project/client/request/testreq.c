#include <stdio.h>
#include "command/utils/cstring.h"
#include "command/utils/cerror.h"
#include "command/utils/cconfig.h"
#include "request.h"

static const char *GENERAL = \
  "Jacke Packe Koda Satan\n\n"
  "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore.\n"\
  "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore.\n"\
  "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore.\n";

int main(void) {
  Print_Header("CLIENT", GENERAL);

  char request[RBUFF] = {'\0'};
  char command[CBUFF] = {'\0'};
  uint32_t request_size = request_driver(request, command);
  printf("reqyesst_size: %d\n", request_size);
  return 0;
}