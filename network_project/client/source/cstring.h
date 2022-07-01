#ifndef CSTRING_H_
#define CSTRING_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "controller.h"

void buffer_flush(char *string, int32_t size_buffer);
int32_t string_size(char *string, int32_t size_buffer);
int32_t string_copy(char *dest, char *from, int32_t size_buffer);
int8_t string_comp(char *str1, const char *str2, int32_t comp_length);
#endif
