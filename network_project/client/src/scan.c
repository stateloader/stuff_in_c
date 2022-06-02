#include "scan.h"

static uint8_t read_scan(scan_t *scan) {

  memset(scan->scanner,'\0', MAX_BUFFER);

  fgets(scan->scanner, MAX_BUFFER - 1, stdin);
  if (!scan->scanner) {
    printf("fgets doesn't respond.\nterminating.\n\n");
    exit(EXIT_FAILURE);
  }

  scan->length = strlen(scan->scanner);
  if (scan->length >= MAX_BUFFER - 1) {
    printf("buffer-limit reached.\nterminating.\n\n");
    exit(EXIT_FAILURE);
  }

  scan->scanner[scan->length - 1] = '\0';
  if (scan->scanner[scan->length - 1] != '\0') {
    printf("input corrupted.\nterminating.\n\n");
    exit(EXIT_FAILURE);
  }
  return ONGOING;
}

static uint8_t byte_scan(scan_t *scan) {

  for (size_t i = 0; i < scan->length; i++) {
    if (!check_ascii(scan->scanner[i])) {
      printf("only English ('ascii') characters allowed. try again!\n\n");
		  return ONGOING;
    }
  }
  return NOGOING;
}

scan_t scan_driver(char *message) {

  scan_t scan;
  uint8_t state = ONGOING;

  while (state != NOGOING) {
    printf("%s> ", message);
    state = read_scan(&scan);
    state = byte_scan(&scan);
	}
  return scan;
}
