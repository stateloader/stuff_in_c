#ifndef SSTRINGS_H_
#define SSTRINGS_H_

#include <stddef.h>
#include <stdint.h>

#define SUCC 1
#define FAIL 0
#define MAX_STR_SIZE 4096

#define check_term(str, size) (str[size - 1] == '\0')

size_t string_size(const char *string);
uint8_t string_copy(uint32_t *size, char *dest, const char *from);

#endif