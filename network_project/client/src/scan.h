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

#define check_ascii(b) (b >= 0x00 && b <= 0x7F)

typedef struct Scan {
  uint8_t status;
  size_t length;
  char scanner[MAX_BUFFER];
} scan_t;

scan_t scan_driver(char *message);

#endif
