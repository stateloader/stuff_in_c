#include <stdio.h>
#include "cconfig.h"
#include "request.h"

int main(void) {

  char request[RBUFF] = {'\0'};
  uint8_t online = 0;

  printf("result: %d\n", request_driver(request, &online));
  return 0;
}