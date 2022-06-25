#ifndef SCANNER_H_
#define SCANNER_H_

#include "configs.h"

#define SCAN_INPUT 0
#define BYTE_CHECK 1
#define SCAN_COMPL 2

#define byte_asci(B) (B >= 0x00 && B <= 0x7F)
#define byte_delm(B) (B == DELIM)

int32_t scan_driver(char *scanner, int32_t size_buffer, char *message);

#endif
