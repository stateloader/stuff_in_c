/*------------------------------------------------------------------------------------------------------------------------
SCAN HEADER
------------------------------------------------------------------------------------------------------------------------*/

#ifndef SCAN_H_
#define SCAN_H_

#define ONGOING 0
#define NOGOING 1

#define check_ascii(B) (B >= 0x00 && B <= 0x7F)
#define check_term(str, len) (str[len - 1] == '\0')
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

#include <stdint.h>
#include <stddef.h>
#include <unistd.h>
#include "utils.h"

typedef struct Scan {
  size_t length;
  char scanner[MAX_BUFFER];
} scan_t;

scan_t scan_driver(char *message);

#endif
