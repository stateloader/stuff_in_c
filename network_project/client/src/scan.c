#include "scan.h"

static void flush_buffer(scan_t *scan) {
/*chararray and length-variable being set to null*/

  for (size_t i = 0; i <= MAX_BUFFER; i++)
    scan->scanner[i] = '\0';
  scan->length = 0;
}

static uint8_t read_scan(scan_t *scan) {
/*flushes the buffer before the user enters her och his input. if the fgets-function
 *having a bad day or the user goes medieaval on the keyboard (reaches 4096 length)
 *we're out.*/

  flush_buffer(scan);
  fgets(scan->scanner, MAX_BUFFER - 1, stdin);
  scan->length = strlen(scan->scanner);
  scan->scanner[scan->length - 1] = '\0';

  if (!scan->scanner) {
    printf("fgets doesn't respond.\nterminating.\n\n");
    return FAIL;

  } else if (scan->length >= MAX_BUFFER - 1) {
    printf("buffer-limit reached.\nterminating.\n\n");
    flush_buffer(scan);
    return FAIL;

  } else if (scan->scanner[scan->length - 1] != '\0') {
    printf("input-string corrupted.\nterminating.\n\n");
    return FAIL;
  }
  return SUCC;
}


static uint8_t byte_scan(scan_t *scan) {
/*mode-arg decides type of input desired.*/

  for (size_t i = 0; i < scan->length; i++) {
    if (!check_ascii(scan->scanner[i])) {
      printf("only English ('ascii') characters allowed. try again!\n\n");
		  return FAIL;
    }
  }
  return SUCC;
}

scan_t scan_driver(char *message) {
/*statemachine of some sort.*/

  scan_t scan;
  uint8_t state = READ_SCAN;

  while (state != QUIT_SCAN) {
  	switch (state) {

  	case READ_SCAN:
    	printf("%s> ", message);
			state = (!read_scan(&scan)) ? QUIT_SCAN : BYTE_SCAN;
			break;
  	case BYTE_SCAN:
    	state = (!byte_scan(&scan)) ? READ_SCAN : QUIT_SCAN;
			break;
  	}
	}
  return scan;
}
