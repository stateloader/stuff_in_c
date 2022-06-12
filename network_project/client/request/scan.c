/*------------------------------------------------------------------------------------------------------------------------
                                                                                                               SCAN MODULE
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cstring.h"
#include "scan.h"

static uint32_t scan_size = 0;

static uint8_t read_byte(char *scan) {

  for (uint32_t i = 0; i < scan_size; i++) {
    if (!check_ascii(scan[i])) {
      printf("only English ('ascii') characters allowed. try again!\n\n");
		  return SCAN;
    }
  }
  return DONE;
}

static uint8_t read_scan(char *scan, uint32_t buffer_size) {

  fgets(scan, buffer_size - 1, stdin);

  if (!scan) {
    printf("fgets doesn't respond.\nterminating.\n\n");
    exit(EXIT_FAILURE);
  }

	scan_size = string_size(scan, buffer_size);
  return read_byte(scan);
}

uint32_t scan_driver(char *scan, uint32_t buffer_size, char *message) {

  uint8_t state = SCAN;

  while (state != DONE) {
		printf("%s> ", message);
		memset(scan,'\0', buffer_size);
    state = read_scan(scan, buffer_size);
	}
  return scan_size;
}
