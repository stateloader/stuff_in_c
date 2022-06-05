#ifndef SCAN_H_
#define SCAN_H_

#include <stddef.h>
#include <stdint.h>

#define SCAN 0
#define DONE 1
#define READ_LIMIT 4096
#define check_ascii(B) (B >= 0x00 && B <= 0x7F)

size_t scan_driver(char *scanner, char *message);

#endif
