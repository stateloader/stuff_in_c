#ifndef SCANNER_H_
#define SCANNER_H_

#include <stddef.h>
#include <stdint.h>

typedef struct scanner {
  uint8_t state;
  int8_t scan_type;
  size_t size_scan;
  size_t size_buff;
  char *scan_input;
  char this_byte;
  uint16_t check;
  uint8_t dcount;
} scan_t;

#define char_check(byte) (byte >= 0x00 && byte <= 0x7F)
//checks if byte is ascii.
#define ints_check(byte) (byte >= '0' && byte <= '9')
//checks if byte is an integer.
#define dots_check(byte) (byte == ',' || byte == '.')
//checks if byte is comma/dot.
#define decm_check(byte) (ints_check(byte) || dots_check(byte))
//checks if byte is an integer or comma/dot.
#define size_check(size) (size >= 2)
//checks if input is at least one char (except terminator).
#define term_check(scan, size) (scan[size - 1] == '\0')
//checks if input is null-terminated.

size_t scan_string(char *user_input, int8_t scan_type, size_t scan_buffer, char *message);
int64_t scan_integer(char *message);
double scan_decimal(char *message);

#endif
