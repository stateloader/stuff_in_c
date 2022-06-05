/*------------------------------------------------------------------------------------------------------------------------
                                                                                                               SCAN MODULE
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strdriver.h"
#include "scan.h"

static uint8_t read_scan(char *scanner, size_t *size) {

  memset(scanner,'\0', READ_LIMIT);

  fgets(scanner, MAX_BUFFER - 1, stdin);
  if (!scanner) {
    printf("fgets doesn't respond.\nterminating.\n\n");
    exit(EXIT_FAILURE);
  }
	*size = string_size(scanner);
  return SCAN;
}

static uint8_t byte_scan(char *scanner, size_t *size) {

  for (size_t i = 0; i < *size; i++) {
    if (!check_ascii(scanner[i])) {
      printf("only English ('ascii') characters allowed. try again!\n\n");
		  return SCAN;
    }
  }
  return DONE;
}

size_t scan_driver(char *scanner, char *message) {

  size_t size = 0;
  uint8_t state = SCAN;

  while (state != DONE) {
    printf("%s> ", message);
    state = read_scan(scanner, &size);
    state = byte_scan(scanner, &size);
	}
  string_test(scanner, size);
  return size;
}
