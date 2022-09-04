/*-----------------------------------------------------------------------------------------CSTRINGS
My own little experiments in making some basic string-functionality.
-------------------------------------------------------------------------------------------------*/
#include <stdlib.h>
#include "cstrings.h"

static uint8_t exit_print(const char *func, const char *cause) {
/*Message printed if something went horrible wrong before terminating the program.*/

	fprintf(stderr, "\nERROR | File [%s] Func [\"%s\"] Time [%s]" \
		"\nCAUSE | %s\nProgram will Terminate...\n",
		__FILE__, func, __DATE__, cause
	);
	exit(EXIT_FAILURE);
}

void buffer_flush(size_t size_buff, char *data_buff) {

  for (size_t i = 0; i < size_buff; i++)
    data_buff[i] = '\0';
  return;
}

size_t string_size(size_t size_buff, const char *data_buff)  {
/*Counting characters until '\0' is reached. NOTE: size/length of a string returned from this bad
 *boy always includes the terminator. The program going to commit seppuku if the loop didn't
 *encountered any terminator within the range of size_buff - 1*/
 
	for (size_t size = 0; size < size_buff - 1; size++) {
    if (data_buff[size] == '\0')
      return size + 1;
  }
  return exit_print("string_size", "no terminator found within buff_range.");
}

size_t string_copy(size_t size_copy_buff, char *copy_buff, const char *from_buff) {
/*Calculates size of the string that should dwell in the from_buff. If this string is larger than the
 *size of the copy_buff a termination will follow, else stuff being copied followed by some last
 *control checks.*/

  size_t size_from = string_size(BUFF_SIZE_LIMIT, from_buff);
    
  if (size_copy_buff < size_from)
  	return exit_print("string_copy", "assigned copy_buffer smaller than size_from.");
  
  size_t size_copy = 0;
	for (size_copy = 0; size_copy < size_from; size_copy++)
		copy_buff[size_copy] = from_buff[size_copy];
	
	if (size_copy != size_from)
		return exit_print("string_copy", "origin and copy of different sizes.");
		
	if (copy_buff[size_copy - 1] != '\0')
		return exit_print("string_copy", "copy not nullterminated.");
		
	return size_copy;
}

/*[Under construction]
size_t string_ccat(size_t size_dest_buff, char *dest_buff, const char *from_buff) {

  size_t size_from = string_size(BUFF_SIZE_LIMIT, from_buff);
  size_t size_dest = string_size(BUFF_SIZE_LIMIT, dest_buff);
  size_t size_both = (size_from + size_dest) - 1;
  
  size_t size_last = 0, size_ccat = 0;

  for (size_last = size_dest - 1, size_ccat = 0; size_last < size_both; size_last++, size_ccat++) {
  	dest_buff[size_last] = from_buff[size_ccat];
  }
	return size_last;
}
*/

int8_t string_comp(size_t comp_size, const char *str1, const char *str2) {
/*For every matching byte, 'equal' will be incremented. If it matches 'comp_size' there's a perfect
 *match and the function will return "true".*/
 
  size_t equal = 0;
  
  for (size_t i = 0; i < comp_size; i++)
    equal += (str1[i] == str2[i]) ? 1 : 0;
  if (equal == comp_size)
  	return 1; 
  return 0;
}

