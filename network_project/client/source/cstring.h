#ifndef CSTRING_H_
#define CSTRING_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

void buffer_flush(char *string, size_t size_buffer);
size_t string_size(const char *string, size_t size_buffer);
size_t string_copy(char *dest, const char *from, size_t size_buffer);
int8_t string_comp(char *str1, const char *str2, size_t comp_length);
#endif
