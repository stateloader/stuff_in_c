#ifndef SCANNER_H_
#define SCANNER_H_

#include <stddef.h>
#include <stdint.h>

typedef struct scanner {
  uint8_t state;
  size_t size_scan;
  size_t size_buff;
  char *scan_input;
} scan_t;

#define asci_check(byte) (byte >= 0x00 && byte <= 0x7F)
#define size_check(size) (size < 2)
#define term_check(scan, size) (scan[size - 1] == '\0')

#define Info_Message(buff) printf("\ninput longer than %ld characters will be cut.\n", buff);
#define Scan_Message(mesg) printf("\t%s\n", mesg);
#define Prompt(mesg) printf("\n%s: ", mesg);

size_t scan_driver(char *scan_input, char *message, size_t size_buffer);

#endif
