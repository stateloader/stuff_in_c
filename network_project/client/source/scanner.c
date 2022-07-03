/*-----------------------------------------------------------------------------------------------------------------SCANNER
Ah, input/scan - strings - is such delight in C... Here I'm using fgets and the user are forbidden from using anything but
English letters ("most of the ASCII-table"). Pipe (|) - DELIM - is forbidden for not screwing any canonical formatting up
and the entire show will come to an end if the user surpass allowed buffer-size.
------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cstring.h"
#include "scanner.h"

static int32_t size_scan = 0;

static int8_t scan_check(char *scan, int32_t size_buffer) {
/*Second state of two where the input being checked. If not OK the user being threwn back to
 *the "input/scan-state" again.
 */
  for (int32_t i = 0; i < size_scan; i++) {
    
    if (!check_byte_asci(scan[i])) {
      System_Message("Only ASCII ('English') characters allowed.");
		  return SCAN_INPUT;

    } else if (check_byte_delm(scan[i])) {
      System_Message("Pipe charachter ('|') is for losers. Use another one.");
      return SCAN_INPUT;
    }
  }
  if (check_scan_minl(size_scan, 2)) {
    System_Message("Enter at least two characters.");
    return SCAN_INPUT;
  }
  if (check_scan_maxl(size_scan, size_buffer)) {
    System_Message("Enter at least two characters.");
    exit(EXIT_FAILURE);
  }
  return SCAN_COMPL;
}

static int8_t scan_input(char *scan, int32_t size_buffer, char *prompt) {
  printf("%s: ", prompt);
  buffer_flush(scan, size_buffer);

  fgets(scan, size_buffer - 1, stdin);
  size_scan = string_size(scan, size_buffer) - 1;
  scan[size_scan  - 1] = '\0';

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
      state = scan_check(scan, size_buffer);
    break;
    default:
      exit(EXIT_FAILURE);
    }
  }
  if (!check_term(scan, size_scan)) {
    System_Message("Failed to terminate userinput.");
    return FAIL;
  }
  return size_scan;
}
