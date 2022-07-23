/*------------------------------------------------------------------------------------------------------------------STRINGS
Same naive approach for string-handeling as in Client. I asume The <libraries> regarding these operations works fine, are
safer and works much efficient but it was/is fun and educational to play around with the stuff myself.                                                                     
/------------------------------------------------------------------------------------------------------------------------*/

#include "cstrings.h"


void buffer_flush(char *buffer, size_t size_buffer) {
/*Nullterminates a buffer.*/

  for (size_t i = 0; i <= size_buffer; i++)
    buffer[i] = '\0';
  return;
}

size_t string_size(const char *string, size_t size_buffer)  {
/*Runs through a string until '\0' is found within the boundaries of 'size_buffer - 1.*/

  for (size_t i = 0; i < size_buffer - 1; i++) {
    if (string[i] == '\0') return i + 1;
  }
  return 0;
}

size_t string_copy(char *dest, const char *from, size_t size_buffer) {
/*Copies from to dest. In some situations this fellah going to ruin the day.*/

  size_t size_from = string_size(from, size_buffer);
  for (size_t i = 0; i < size_from; i++)
    dest[i] = from[i];
  return size_from;
}

int8_t string_comp(char *str1, const char *str2, size_t comp_buff) {
/*Compares two strings by increment 'match' for every equal byte between str1, str2.*/

  size_t match = 0;
  for (size_t i = 0; i < comp_buff; i++)
    match += (str1[i] == str2[i]) ? 1 : 0;
  if (match == comp_buff)
    return 1;
  return 0;
}

