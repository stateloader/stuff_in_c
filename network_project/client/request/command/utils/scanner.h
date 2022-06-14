#ifndef SCANNER_H_
#define SCANNER_H_

#include <stddef.h>
#include <stdint.h>

#define SCAN_INPUT 0
#define BYTE_CHECK 1
#define SCAN_COMPL 2

int32_t scan_driver(char *scanner, int32_t size_buffer, char *message);

#endif
