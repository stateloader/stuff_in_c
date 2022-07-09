
#ifndef CSTRINGS_H_
#define CSTRINGS_H_
#include "configs.h"

void buffer_flush(char *string, size_t size_buffer);

size_t string_size(const char *string, size_t size_buffer);
size_t string_copy(char *dest, const char *from, size_t size_buffer);
int8_t string_comp(char *str1, const char *str2, size_t comp_length);
size_t string_ccat(char *dest, const char *from, size_t ccat_buffer);

#endif
