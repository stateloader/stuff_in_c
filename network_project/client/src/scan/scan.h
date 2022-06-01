/*-------------------------------------------------------------------------------------
																																						SCAN MODULE
---------------------------------------------------------------------------------------
GENERAL
---------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------*/

#ifndef SCAN_H_
#define SCAN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

#define MAX_BUFFER 4096

#define FAIL 0
#define SUCC 1

#define READ_SCAN 0
#define BYTE_SCAN 1
#define QUIT_SCAN 2

#define check_ascii(b) (b >= 0x00 && b <= 0x7F)
#define check_alpha(b) (b >= 'a' && b <= 'Z')
#define check_digit(b) (b >= '0' && b <= '9')

typedef struct Scan {
  size_t length;
  char scanner[MAX_BUFFER];
} scan_t;

scan_t scan_driver(char *message);

#endif
