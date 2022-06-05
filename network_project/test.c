#include <stdio.h>
#include "client/strdriver.h"
#include "client/scan.h"

int main(void) {

  char input1[READ_LIMIT] = "hej";
  char input2[READ_LIMIT] = "hopp";

 // scan_driver(input1, "first string");
 // scan_driver(input2, "second string");

  string_merge(input1, input2);

  printf("input1 (merged), %s\n", input1);
  return 0;
}
