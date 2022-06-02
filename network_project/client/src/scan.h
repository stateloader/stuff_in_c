/*-------------------------------------------------------------------------------------
																																						SCAN MODULE
---------------------------------------------------------------------------------------
GENERAL
---------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------*/

#ifndef SCAN_H_
#define SCAN_H_

#include "utils.h"

//#define FAIL 0
//#define SUCC 1

#define ONGOING 0
#define NOGOING 1

#define check_ascii(B) (B >= 0x00 && B <= 0x7F)

typedef struct Scan {
  size_t length;
  char scanner[MAX_BUFFER];
} scan_t;

scan_t scan_driver(char *message);

#endif
