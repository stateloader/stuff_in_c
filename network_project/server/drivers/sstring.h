#ifndef SSTRING_H_
#define SSTRING_H_

#include "controller.h"

void buffer_flush(char *buffer, int32_t size_buffer);
int32_t string_size(const char *string, int32_t size_buffer);
int32_t string_copy(char *dest, const char *from, int32_t size_buffer);
int8_t string_comp(char *str1, const char *str2, int32_t comp_length);

#endif