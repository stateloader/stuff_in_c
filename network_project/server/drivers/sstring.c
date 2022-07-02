/*----------------------------------------------------------------------------------------------------------SSTRING MODULE
                                                                                                            
------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sstring.h"

void buffer_flush(char *buffer, int32_t size_buffer) {
  for (int32_t i = 0; i <= size_buffer; i++)
    buffer[i] = '\0';
}

int32_t string_size(const char *string, int32_t size_buffer)  {
  for (int32_t i = 0; i < size_buffer - 1; i++) {
    if (string[i] == '\0') 
      return (i + 1);
  }
  return 0;
}

int32_t string_copy(char *dest, const char *from, int32_t size_buffer) {
  int32_t size_from = string_size(from, size_buffer);
  for (int32_t i = 0; i < size_from; i++)
    dest[i] = from[i];
  dest[size_from - 1] = '\0';
  return size_from;
}

int8_t string_comp(char *str1, const char *str2, int32_t comp_buff) {

  int32_t match = 0;
  for (int32_t i = 0; i < comp_buff; i++)
    match += (str1[i] == str2[i]) ? 1 : 0;
  if (match == comp_buff)
    return SUCC;
  return FAIL;
}