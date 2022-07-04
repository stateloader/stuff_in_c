/*-----------------------------------------------------------------------------------------------------------CLIENT STRING

------------------------------------------------------------------------------------------------------------------------*/

#include "cstring.h"

void buffer_flush(char *buffer, size_t size_buffer) {
  for (size_t i = 0; i <= size_buffer; i++)
    buffer[i] = '\0';
}

size_t string_size(const char *string, size_t size_buffer)  {
  for (size_t i = 0; i < size_buffer - 1; i++) {
    if (string[i] == '\0') return (i + 1);
  }
  return 0;
}

size_t string_copy(char *dest, const char *from, size_t size_buffer) {
  size_t size_from = string_size(from, size_buffer);
  for (size_t i = 0; i < size_from; i++)
    dest[i] = from[i];
  return size_from;
}

int8_t string_comp(char *str1, const char *str2, size_t comp_buff) {

  size_t match = 0;

  for (size_t i = 0; i < comp_buff; i++)
    match += (str1[i] == str2[i]) ? 1 : 0;

  if (match == comp_buff)
    return SUCC;
  return FAIL;
}