#ifndef CSTRING_H_
#define CSTRING_H_

#include <stddef.h>
#include <stdint.h>

void buffer_flush(char *string, int32_t buffer_size);
int32_t string_size(char *string, int32_t buffer_size);
int8_t string_comp(char *str1, const char *str2, int32_t comp_length);

#endif
