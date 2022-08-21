/*------------------------------------------------------------------------------------------Scanner
Logic for string, integer and double-input. "Main function" is 'scan_string' with args:

-user_input;  pointer to the buffer in which the input will be stored.
-scan_type;   input-type, 0 = string, 1 = integer, 2 = decimal.
-size_buffer; size of input-buffer (user_input).
-message;     prompt/message for the user.

Current config only allows ASCII-chars and the user must input at least one char. On the other end,
input will be cut and terminated if 'size_buff' is reached.
-------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include "cstrings.h"
#include "scanner.h"

typedef struct ScanInfo {
	const uint16_t info_code;
	const char *mesg;
} info_item;

static const uint16_t TERM_FAIL = 0; // string isn't terminated.
static const uint16_t INFO_SIZE = 1; // string is lesser than 1 char.
static const uint16_t INFO_ASCI = 2; // string contains anything but ASCII.
static const uint16_t INFO_NUMB = 3; // string contains anything but integer.
static const uint16_t INFO_FDCH = 4; // string doesn't begin with an integer.
static const uint16_t INFO_NCOM = 5; // string contains two dots/commas.
static const uint16_t INFO_MCOM = 6; // string doesn't contain dots/commas or integer.

//Current Info-flags/bits that will be set in the'check'-member ('scan'-instance) if the user
//violates an expected input behaviour.

static info_item info_items[] = {
  {TERM_FAIL, "input is corrupted, terminating program.\n"},
  {INFO_SIZE, "enter at least one character.\n"},
  {INFO_ASCI, "only ASCII (\"English characters\") allowed.\n"},
  {INFO_NUMB, "only integers allowed.\n"},
  {INFO_FDCH, "first character must be an integer.\n"},
  {INFO_NCOM, "only one comma allowed.\n"},
  {INFO_MCOM, "only one comma and digits allowed.\n"},
};

static const uint8_t STATE_SCAN = 0, STATE_DONE = 1;

static void scan_info(scan_t *scan) {
/*By and:ing every bit in 'scan->check' with every 'info_code'-member in 'info_items', corresponding
 *'mesg'-member will be printed. Input logic will be ran again in all cases execept if a failed
 *string-termination is detected which going to force quit the entire program.*/
 
  for (size_t i = 0; i < array_size(info_items); i++) {
    if (scan->check & (1 << info_items[i].info_code))
    printf("%s\n", info_items[i].mesg);
  }
  if (scan->check & (1 << TERM_FAIL))
    exit(EXIT_FAILURE);
  
  scan->check = 0x00;
  scan->state = STATE_SCAN;
  scan->dcount = 0;
  return;
}

static void check_string(scan_t *scan) {
/*String-scan check(s).*/
  
  scan->check |= (!char_check(scan->this_byte)) ? (1 << INFO_ASCI) : (0 << INFO_ASCI);
  return;
}

static void check_integer(scan_t *scan) {
/*Integer-scan check(s).*/

  scan->check |= (!ints_check(scan->this_byte)) ? (1 << INFO_NUMB) : (0 << INFO_NUMB);
  return;
}

static void check_decimal(scan_t *scan) {
/*Decimal-scan check(s).*/

  scan->dcount += (dots_check(scan->this_byte)) ? 1 : 0;

	scan->check |= (!ints_check(scan->scan_input[0])) ? (1 << INFO_FDCH) : (0 << INFO_FDCH);
	scan->check |= (!decm_check(scan->this_byte)) ? (1 << INFO_MCOM) : (0 << INFO_MCOM);
	scan->check |= (scan->dcount > 1) ? (1 << INFO_NCOM) : (0 << INFO_NCOM);
	return;
}

static void scan_check(scan_t *scan) {
/*Some generic checks before type specific checks. Later is dealt with in the 'check'-functions
 *above and called from a func-ptr array ('check_funcs'), indexed by 'input_type'.*/

	void (*check_funcs[])(scan_t *scan) = {check_string, check_integer, check_decimal};

  scan->check |= (!term_check(scan->scan_input, scan->size_scan)) ? (1 << TERM_FAIL) : (0 << TERM_FAIL);
  scan->check |= (!size_check(scan->size_scan)) ? (1 << INFO_SIZE) : (0 << INFO_SIZE);
  if (scan->check > 0)
    return scan_info(scan);
  
  for (size_t i = 0; i < scan->size_scan - 1; i++) {
    scan->this_byte = scan->scan_input[i];
  	(*check_funcs[scan->scan_type])(scan);
  	if (scan->check > 0)
  	  return scan_info(scan);
  }
  scan->state = STATE_DONE;
  
  return;
}

static void scan_input(scan_t *scan, char *message) {
/*Utilizing fgets during input. When user has hit enter, '\n' is swapped for '\0' before the input
 *is checked within the 'scan_check'-function.*/

	printf("%s> ", message);
  buffer_flush(scan->scan_input, scan->size_buff);

  fgets(scan->scan_input, scan->size_buff, stdin);
  scan->size_scan = string_size(scan->scan_input, scan->size_buff) - 1;
  scan->scan_input[scan->size_scan - 1] = '\0';
  
  return scan_check(scan);
}

static scan_t scan_setup(char *user_input, int8_t scan_type, size_t scan_buff) {
/*<missing comment>.*/
  scan_t scan = {0};
  
  scan.state = STATE_SCAN;
  scan.scan_type = scan_type;
  scan.size_buff = scan_buff;
  scan.scan_input = user_input;
  
  return scan;
}

size_t scan_string(char *user_input, int8_t scan_type, size_t size_buff, char *message) {
/*<missing comment>.*/
 
  scan_t scan = scan_setup(user_input, scan_type, size_buff);
  
  while (scan.state != STATE_DONE)
    scan_input(&scan, message);
       
  return scan.size_scan;
}

int64_t scan_integer(char *message) {	
/*Integer scan.*/

	char integer_buffer[16] = {'\0'};
	
	scan_string(integer_buffer, 1, 16, message);
	int64_t integer = atoi(integer_buffer);
	
	return integer;
}

double scan_decimal(char *message) {  
/*Double scan.*/

	char decimal_buffer[16] = {'\0'};
	
	scan_string(decimal_buffer, 2, 16, message);
	double decimal = atof(decimal_buffer);
	
	return decimal;
}
