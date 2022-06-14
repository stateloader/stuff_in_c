#ifndef CSTRING_H_
#define CSTRING_H_

#include <stddef.h>
#include <stdint.h>

#define check_ascii(B) (B >= 0x00 && B <= 0x7F)
#define check_size(scans, buffs) (scans < buffs - 1) 
#define check_term(scan, size) (scan[size - 1] == '\0')

void buffer_flush(char *string, int32_t buffer_size);
int32_t string_size(char *string, int32_t buffer_size);
int8_t string_comp(char *str1, const char *str2, int32_t comp_length);

#endif
