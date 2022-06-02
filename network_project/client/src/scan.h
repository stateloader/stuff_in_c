/*-------------------------------------------------------------------------------------
																																						SCAN MODULE
---------------------------------------------------------------------------------------
GENERAL
---------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------*/

#ifndef SCAN_H_
#define SCAN_H_

#include "utils.h"

#define FAIL 0
#define SUCC 1

#define READ_SCAN 0
#define BYTE_SCAN 1
#define QUIT_SCAN 2

#define check_ascii(B) (B >= 0x00 && B <= 0x7F)
#define check_term(S, L) (S[L - 1] == '\0')

typedef struct Scan {
  size_t length;
  char scanner[MAX_BUFFER];
} scan_t;

scan_t scan_driver(char *message);

#endif
