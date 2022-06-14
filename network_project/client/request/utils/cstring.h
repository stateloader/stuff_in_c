#ifndef CSTRING_H_
#define CSTRING_H_

#include <stddef.h>
#include <stdint.h>

void buffer_flush(char *string, uint32_t buffer_size);
uint32_t string_size(char *string, uint32_t buffer_size);
int8_t string_comp(char *str1, const char *str2, uint32_t comp_length);

#endif
