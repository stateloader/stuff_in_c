#include <stdio.h>
#include <stdlib.h>
#include "cstrings.h"
#include "scanner.h"

static const uint8_t STATE_SCAN = 0, STATE_REDO = 1, STATE_DONE = 2;

static void scan_check(scan_t *scan) {
/*Some (current) checks to be fulfilled before the state-member flags session completed.*/ 

  for (size_t i = 0; i < scan->size_scan; i++) {
  	if (!asci_check(scan->scan_input[i])) {
      Scan_Message("only ASCII (\"English characters\") allowed.");
      scan->state = STATE_REDO; break;
    }
  } if (size_check(scan->size_scan)) {
  	Scan_Message("enter at least one character.");
  	scan->state = STATE_REDO;
  } if (!term_check(scan->scan_input, scan->size_scan)) {
  	Scan_Message("input is corrupted, terminating program.");
  	exit(EXIT_FAILURE);
  }//	Bad news. Input isn't correctly terminated. System commits seppuku.
 
  scan->state = (scan->state == STATE_REDO) ? STATE_SCAN : STATE_DONE;
}

static void scan_input(scan_t *scan, char *prompt) {
/*Utilizing fgets during input. When done, NL is swapped for \0 before the string being checked.*/

	Prompt(prompt);
  buffer_flush(scan->scan_input, scan->size_buff);

  fgets(scan->scan_input, scan->size_buff - 1, stdin);
  scan->size_scan = string_size(scan->scan_input, scan->size_buff) - 1;
  scan->scan_input[scan->size_scan - 1] = '\0';

  scan_check(scan);
  
  return;
}

size_t scan_driver(char *user_input, char *prompt, size_t size_buffer) {
/*An instance of type "scan_t" being created. Its 'scan_input'-member will point at the address of
 *an input-buffer (arg 'user_input') before the show begins.*/
  
  scan_t scan = {.state = STATE_SCAN,.size_buff = size_buffer};
  scan.scan_input = user_input;

  while (scan.state != STATE_DONE)
  	scan_input(&scan, prompt);
   
  return scan.size_scan;
}
