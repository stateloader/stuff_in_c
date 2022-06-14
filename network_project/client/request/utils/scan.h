#ifndef SCAN_H_
#define SCAN_H_

#include <stddef.h>
#include <stdint.h>

#define SCAN_INPUT 0
#define BYTE_CHECK 1
#define SCAN_COMPL 2

#define check_ascii(B) (B >= 0x00 && B <= 0x7F)
int8_t scan_driver(char *scanner, uint32_t size_buffer, char *message);

#endif
