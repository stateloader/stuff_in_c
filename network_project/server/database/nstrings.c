/*------------------------------------------------------------------------------------------------------------------------
                                                                                                            NSTRING MODULE
--------------------------------------------------------------------------------------------------------------------------
info fasda
------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"
#include "nstrings.h"

size_t string_size(const char *string) {
  return strnlen(string, MAX_STR_SIZE); 
}

uint8_t string_copy(size_t *size, char *dest, const char *from) {
  
  *size = string_size(from) + 1;

  if (sizeof(dest) > *size - 1) {
    String_Error_Message("string_copy", "size of dest lesser than from", from);
    return ABORT;
  }

  strncpy(dest, from, *size);

  dest[*size - 1] = '\0';
  if (!check_term(dest, *size)) {
    String_Error_Message("string_copy", "failed to nullterminate\n", dest);
    return FATAL;
  }
  return VALID;
}