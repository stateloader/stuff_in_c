/*------------------------------------------------------------------------------------------------------------------STRINGS
Same naive approach for string-handeling as in Server. I assume The <libraries> regarding these operations works fine, are
safer and works much efficient but it was/is fun and educational to play around with by myself.                                                                     
-------------------------------------------------------------------------------------------------------------------------*/

#include "cstrings.h"

void buffer_flush(char *buffer, size_t size_buffer) {
/*Nullterminates a buffer.*/

  for (size_t i = 0; i <= size_buffer; i++)
    buffer[i] = '\0';
}

size_t string_size(const char *string, size_t size_buffer)  {
/*Runs through a string until '\0' is found within the boundaries of 'size_buffer - 1. Returns index of '\0' + 1 or
 *0 if no terminator was detected.*/

  for (size_t i = 0; i < size_buffer - 1; i++) {
    if (string[i] == '\0') return i + 1;
  }
  return 0;
}

size_t string_copy(char *dest, const char *from, size_t size_buffer) {
/*Copies from to dest. I know, at the moment some grave situations where this bad boy can ruin the day.*/

  size_t size_from = string_size(from, size_buffer);
  for (size_t i = 0; i < size_from; i++)
    dest[i] = from[i];
  return size_from;
}

int8_t string_comp(char *str1, const char *str2, size_t comp_buff) {
/*Compares two strings by increment 'match' for every equal byte between str1, str2. Tailored to be used where I've a
 *desire to know two strings are exactly the same; no less or more (command module in Client, for example).*/

  size_t match = 0;
  for (size_t i = 0; i < comp_buff; i++)
    match += (str1[i] == str2[i]) ? 1 : 0;
  if (match == comp_buff)
    return 1;
  return 0;
}
