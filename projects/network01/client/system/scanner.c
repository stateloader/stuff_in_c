/*--------------------------------------------------------------------------------------------SCANNER
Basic userinput.
---------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "cstrings.h"
#include "scanner.h"

static uint8_t fail_print(const char *mesg) {
/*Message (mesg) is printed if any check-condition is violated. Return-value going to be 0 which tells
 *the while-loop wrapping the entire circus to redo the input-session.*/
 
	printf("%s\n\n", mesg);
	return 0;
}

static uint8_t exit_print(const char *func, const char *cause) {
/*Something went horrible. Terminates the program.*/

	fprintf(stderr, "\nERROR | File [%s] Func [\"%s\"] Time [%s]" \
		"\nCAUSE | %s\nProgram will Terminate...\n",
		__FILE__, func, __DATE__, cause
	);
	exit(EXIT_FAILURE);
}

static uint8_t asci_check(formc_t *asci) {
/*Ascii (format) check.*/

  for (size_t i = 0; i < asci->size_data - 1; i++) {
  	if (!ASCI_CHECK(asci->data_buff[i]))
  		return fail_print("only ASCII (\"English letters\") allowed.");
  }
  return 1;
}

static uint8_t intg_check(formc_t *intg) {
/*Integer (format) check.*/

  for (size_t i = 0; i < intg->size_data - 1; i++) {
		if (!INTG_CHECK(intg->data_buff[i]))
      return fail_print("only integers allowed.");
  }
  return 1;
}

static inline uint8_t decm_inline(guard_t *guard) {
/*Byte for byte cruncher inside the upcoming 'decm_check'-func.*/

  if (!DECM_CHECK(guard->byte))
    return fail_print("corrupted format; invalid character.");
    
  guard->delm_count += (PERD_CHECK(guard->byte)) ? 1 : 0;
  if (guard->delm_count > 1)
  	return fail_print("corrupted format; only one period allowed.");
  return 1;
}

static uint8_t decm_check(formc_t *decm) {
/*decimal (format) check.*/

  guard_t guard = {.state = ONLY_INTG};
	
	if (!INTG_CHECK(decm->data_buff[0]))
		return fail_print("corrupted format; first character must be an integer.");
		
  for (size_t i = 0; i < decm->size_data - 1; i++) {
    guard.byte = decm->data_buff[i];
      if (!decm_inline(&guard))
        return 0;
  }
  return 1;
}
static inline uint8_t ipv4_inline(guard_t *guard) {
/*Byte for byte cruncher inside the upcoming 'ipv4_check'-func.*/

  if (!IPV4_CHECK(guard->byte))
    return fail_print("corrupted format; invalid character.");

  switch(guard->state) {
  case ONLY_DELM:
    if (!PERD_CHECK(guard->byte))
      return fail_print("corrupted format; more than 3 digits in octet(s).");
    guard->delm_count += 1;
    guard->state = ONLY_INTG;
    break;
  
  case ONLY_INTG:
    if (!INTG_CHECK(guard->byte))
      return fail_print("corrupted format; two periods in a row.");
    guard->intg_count += 1;
    guard->state = THIS_CONF;
    break;
    
  case THIS_CONF:
    guard->intg_count += (INTG_CHECK(guard->byte)) ? 1 : 0;
    if (guard->intg_count == 3) {
      guard->intg_count = 0;
      guard->state = ONLY_DELM;
    } else {
      guard->state = THIS_CONF;
    }
    break;
  default:
  	exit_print("ipv4_form", "default reached in switch statement");
  }
  return 1;
}

static uint8_t ipv4_check(formc_t *ipv4) {
/*ipv4 (format) check.*/
  
  guard_t guard = {.state = ONLY_INTG};
  
  if (!IPV4_RANGE(ipv4->size_data))
  	return fail_print("corrupted size; address size outside range 7 to 15.");
  
  if (!INTG_CHECK(ipv4->data_buff[0]))
  	return fail_print("corrupted format; first character not an integer.");
  
  for (size_t i = 0; i < ipv4->size_data - 1; i++) {
    guard.byte = ipv4->data_buff[i];
    if (!ipv4_inline(&guard)) return 0;
  }
  return 1;
}

static uint8_t ipv6_check(formc_t *ipv6) {
/*IPv6 format check (to be).*/
	
  for (size_t i = 0; i < ipv6->size_data - 1; i++) {
  	if (!IPV6_CHECK(ipv6->data_buff[i]))
  	  return fail_print("yolo\n");
  }
  return 1;
}

typedef uint8_t (*form_func)(formc_t *scan);

typedef struct FormatPlugin {
	form_func func;
} form_plug;

static form_plug form_plugs[] = {
  {asci_check}, {intg_check}, {decm_check},
  {ipv4_check}, {ipv6_check}, // so far.
};

//---------------------------------------------------------------------------------------------------

static uint8_t scan_check(uint8_t plugin, size_t size_data, char *data_buff) {
/*Desired 'plugin'-value is assigned to the member (struct-variable 'data' of type 'formc_t') with
 *the same name. 'data' is used as a bucket to carry assigned value(s)/references to the the
 *'scan_check'-args down the stack.*/

	formc_t data = {.plugin = plugin,.size_data = size_data,.data_buff = data_buff};
	
	if (MINS_CHECK(data.size_data))
	  return fail_print("enter at least one character.");
	
	if (!SPAN_CHECK(data.plugin, SIZE_ARRAY(form_plugs)))
		return exit_print("format_check", "value of item-arg out of range.");
	
	if (!TERM_CHECK(data.data_buff[data.size_data]))
    return exit_print("format_check", "string not terminated");
    
	return form_plugs[data.plugin].func(&data);
}

static uint8_t scan_input(scan_t *scan, char *message) {
/*Utilizing fgets for input. The logic demands input of at least one character by compiled default. The
 *input will be cut and automatically added a terminator if the user reaches the upper buff-limit.*/
 
	printf("%s> ", message);
  buffer_flush(scan->size_buff, scan->scan_buff);

  fgets(scan->scan_buff, scan->size_buff, stdin);
  scan->size_scan = string_size(scan->size_buff, scan->scan_buff) - 1;
  scan->scan_buff[scan->size_scan - 1] = '\0';

  return scan_check(scan->plugin, scan->size_scan, scan->scan_buff);
}

size_t scan_driver(uint8_t plugin, size_t size_buff, char *read_buff, char *message) {
/*I tend to call all "main-functions" for 'drivers' and this is no exception. Func-params being assigned/
 *pointed to by the members in struct-variable 'scan' before everything being thrown into 'scan_input'.*/
  
  scan_t scan = {.state = 0,.plugin = plugin,.size_buff = size_buff,.scan_buff = read_buff};
  
  while (scan.state != 1)
    scan.state = scan_input(&scan, message);
  
  return scan.size_scan;
}
