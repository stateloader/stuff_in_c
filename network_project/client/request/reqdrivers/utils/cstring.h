#ifndef CSTRING_H_
#define CSTRING_H_

#include <stddef.h>
#include <stdint.h>

void buffer_flush(char *string, int32_t size_buffer);
int32_t string_size(char *string, int32_t size_buffer);
int32_t string_copy(char *dest, char *from, int32_t size_buffer);
int8_t string_comp(char *str1, const char *str2, int32_t comp_length);
#endif
