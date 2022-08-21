#include <stdio.h>
#include <stdlib.h>
#include "cstrings.h"
#include "scanner.h"

int main(void) {

  char scan_buff[512] = {'\0'};
  size_t size_scan = scan_string(scan_buff, 0, 512, "enter awesome string");

  int64_t integer = scan_integer("enter awesome integer");
  double decimal = scan_integer("enter awesome double");

  printf("string:   %s [size: %ld]\ninteger:  %ld\ndouble:   %lf\n", scan_buff, size_scan - 1, integer, decimal);

  return 0;
}
