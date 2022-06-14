/*------------------------------------------------------------------------------------------------------------------------
                                                                                                               SCAN MODULE
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cerror.h"
#include "cstring.h"
#include "scan.h"

static int32_t size_scan = 0;

static int8_t scan_check(char *scan) {

  for (int32_t i = 0; i < size_scan; i++) {
    if (!check_ascii(scan[i])) {
      Print_Warning("only English ('ascii') characters allowed. try again!");
		  return SCAN_INPUT;
    }
  }
  return SCAN_COMPL;
}

static int8_t scan_input(char *scan, uint32_t size_buffer, char *message) {
  
  printf("\n%s: ", message);
  buffer_flush(scan, size_buffer);

  fgets(scan, size_buffer - 1, stdin);
  size_scan = string_size(scan, size_buffer) - 1;
  scan[size_scan  - 1] = '\0';
  
  return String_Check(SVSIZE, "read_scan", scan, size_scan - 1, size_buffer);
}

int32_t scan_driver(char *scan, uint32_t size_buffer, char *message) {

  uint8_t state = SCAN_INPUT;
  while (state != SCAN_COMPL) {
    switch(state) {
    case SCAN_INPUT:
      state = scan_input(scan, size_buffer, message);
      break;
    case BYTE_CHECK:
      state = scan_check(scan);
    break;
    default:
      exit(EXIT_FAILURE);
    }
  }
  String_Check(SSTERM, "scan_driver", scan, size_scan, size_buffer);
  return size_scan;
}