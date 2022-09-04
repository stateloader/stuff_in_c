#include <stdio.h>
#include <stdlib.h>
#include "cstrings.h"
#include "scanner.h"

int main(void) {

  char read_buff[512] = {'\0'};
  size_t size_scan = scan_driver(ASCI_PLUG, 512, read_buff, "enter awesome string");

  printf("awesome string:  %s [size: %ld]\n", read_buff, size_scan - 1);

  return 0;
}
