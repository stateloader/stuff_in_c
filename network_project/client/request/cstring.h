#ifndef CSTRING_H_
#define CSTRING_H_

#include <stddef.h>
#include <stdint.h>

#define check_term(str, len) (str[len - 1] == '\0')

void string_test(char *string, uint32_t size);
uint32_t string_size(char *string, uint32_t buffer_size);
uint8_t string_comp(char *str1, const char *str2, uint32_t comp_length);

#endif
