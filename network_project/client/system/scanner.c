/*------------------------------------------------------------------------------------------------------------------Scanner
Scan/input from the user utilizing fgets. Only English (most of "ASCII"-table) is allowed except the pipe character ('|').
It governs how most of various processes on both client- and serverside behave and would screw up things rather badly if
the user was allowed to use it =)
-------------------------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cstrings.h"
#include "scanner.h"

static void scan_byte(scan_t *scanner) {
/*Checks user-input byte for byte not containing any "forbidden" charachter*/

  for (size_t i = 0; i < scanner->size_scan; i++) {
    
    if (!scan_check_asci(scanner->scan_input[i])) {
      System_Message("only ASCII ('English') characters allowed.");
      scanner->state = SSCAN;
      return;
    }
    if (scan_check_delm(scanner->scan_input[i])) {
      System_Message("pipe charachter ('|') is for losers. Use another one.");
      scanner->state = SSCAN; 
      return;
    }
  } if (!scan_check_term(scanner->scan_input, scanner->size_scan)) {
    System_Message("input not nullterminated. terminating.");
    exit(EXIT_FAILURE);
  }
  scanner->state = SDONE;
}

static void scan_size(scan_t *scanner) {
/*Checks input is within the boarders for allowed input-sizes (max 'broken' at the moment)*/

  if (scan_check_minl(scanner->size_scan, 1)) {
    System_Message("enter at least one character.");
    scanner->state = SSCAN;
    return;
  }
  if (scan_check_maxl(scanner->size_scan, scanner->size_buff)) {
    System_Message("you've passed allowed input-limit. Yay!");
    exit(EXIT_FAILURE);
  }
  scanner->state = SDONE;
}

static void scan_input(scan_t *scanner, char *prompt) {

  printf("%s: ", prompt);
  buffer_flush(scanner->scan_input, scanner->size_buff);

  fgets(scanner->scan_input, scanner->size_buff - 1, stdin);
  scanner->size_scan = string_size(scanner->scan_input, scanner->size_buff) - 1;
  scanner->scan_input[scanner->size_scan  - 1] = '\0';

  scanner->state = SSCHK;
}

size_t scan_driver(char *user_input, char *prompt, size_t size_buffer) {
/*State-machine of some sort dealing with input and some checks.*/

  scan_t scanner = {.state = SSCAN,.size_buff = size_buffer};
  scanner.scan_input = user_input;

  while (scanner.state != SDONE) {

    switch(scanner.state) {
    case SSCAN:
      scan_input(&scanner, prompt);
    break;
    case SSCHK:
      scan_size(&scanner);
    break;
    case SBCHK:
      scan_byte(&scanner);
    break;
    default:
      System_Message("ScanError - Reached default for some reason.");
      exit(EXIT_FAILURE);
    }
  }
  return scanner.size_scan;
}
