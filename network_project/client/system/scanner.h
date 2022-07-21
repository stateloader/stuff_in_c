#ifndef SCANNER_H_
#define SCANNER_H_

#include "configs.h"

#define SSCAN 0  // State Scan.
#define SSCHK 1  // State Size Check.
#define SBCHK 2  // State Byte Check. 
#define SDONE 3  // State Done.

typedef struct scanner {
  uint8_t state;
  size_t size_scan;
  size_t size_buff;
  char *scan_input;
} scan_t;

#define scan_check_asci(byte) (byte >= 0x00 && byte <= 0x7F)
#define scan_check_delm(byte) (byte == DELIM)
#define scan_check_term(scan, size) (scan[size - 1] == '\0')
#define scan_check_minl(size, minl) (size <= minl)
#define scan_check_maxl(size, maxl) (size >= maxl)

size_t scan_driver(char *scan_input, char *message, size_t size_buffer);

#endif
