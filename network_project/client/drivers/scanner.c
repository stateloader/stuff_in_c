/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                   SCANNER
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cconfig.h"
#include "cstring.h"
#include "scanner.h"

static int32_t size_scan = 0;

static int8_t scan_check(char *scan) {

  for (int32_t i = 0; i < size_scan; i++) {
    if (!byte_asci(scan[i])) {
      System_Message("Only ASCII ('English') characters allowed. try again!")
		  return SCAN_INPUT;
    } else if (byte_delm(scan[i])) {
      System_Message("Pipe charachter ('|') is for losers, use another one.")
    }
  }
  return SCAN_COMPL;
}

static int8_t scan_input(char *scan, int32_t size_buffer, char *message) {
  
  printf("%s: ", message);
  buffer_flush(scan, size_buffer);

  fgets(scan, size_buffer - 1, stdin);
  size_scan = string_size(scan, size_buffer) - 1;
  scan[size_scan  - 1] = '\0';
  
  if (!check_size(size_scan, size_buffer)) {
    printf("input to large.\n");
    buffer_flush(scan, size_buffer);
    return SCAN_INPUT;
  }
  return BYTE_CHECK;
}

int32_t scan_driver(char *scan, int32_t size_buffer, char *message) {

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
  if (!check_term(scan, size_scan))
    return - 1;
  return size_scan;
}