#include <stdio.h>
#include "cutils/cstring.h"
#include "cutils/cerror.h"
#include "cutils/cconfig.h"
#include "request.h"

int main(void) {

  char request[RBUFF];
  uint8_t online = 0;

  printf("result: %d\n", request_driver(request, &online));

  uint32_t size = string_size(request, RBUFF);
  String_Check(SSTERM, "main", request, size, RBUFF);
  printf("request: %s\nsize: %d\n", request, size);
  return 0;
}