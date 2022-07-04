#ifndef SCANNER_H_
#define SCANNER_H_

#include "config.h"

#define SCAN_INPUT 0
#define BYTE_CHECK 1
#define SCAN_COMPL 2

#define check_byte_asci(byt) (byt >= 0x00 && byt <= 0x7F)
#define check_byte_delm(byt) (byt == DELIM)
#define check_scan_minl(len, min) (len <= min)
#define check_scan_maxl(len, max) (len >= max)

int32_t scan_driver(char *scanner, int32_t size_buffer, char *message);

#endif
