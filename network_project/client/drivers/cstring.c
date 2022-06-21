/*------------------------------------------------------------------------------------------------------------------------
                                                                                                             CLIENT STRING
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/

#include "cstring.h"

void buffer_flush(char *buffer, int32_t size_buffer) {
  for (int32_t i = 0; i <= size_buffer; i++)
    buffer[i] = '\0';
}

int32_t string_size(char *string, int32_t size_buffer)  {
  for (int32_t i = 0; i < size_buffer - 1; i++) {
    if (string[i] == '\0') return (i + 1);
  }
  return 0;
}

int32_t string_copy(char *dest, char *from, int32_t size_buffer) {
  int32_t size_from = string_size(from, size_buffer);
  for (int32_t i = 0; i < size_from; i++)
    dest[i] = from[i];
  return size_from;
}
/*

int32_t string_ucpy(uint8_t *dest, char *from, int32_t size_buffer) {
  int32_t size_from = string_size(from, size_buffer);
  for (int32_t i = 0; i < size_from; i++)
    dest[i] = (uint8_t) from[i];
  return size_from;
}
*/
int8_t string_comp(char *str1, const char *str2, int32_t comp_buff) {

  int32_t match = 0;
  for (int32_t i = 0; i < comp_buff; i++)
    match += (str1[i] == str2[i]) ? 1 : 0;
  if (match == comp_buff)
    return SUCC;
  return FAIL;
}