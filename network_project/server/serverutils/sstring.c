/*------------------------------------------------------------------------------------------------------------------------
                                                                                                            NSTRING MODULE
--------------------------------------------------------------------------------------------------------------------------
info fasda
------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sstring.h"

size_t string_size(const char *string) {
  for (size_t i = 0; i < MAX_STR_SIZE; i++) {
    if (string[i] == '\0')
      return i;
  }
  return 0;
}

uint8_t string_copy(uint32_t *size, char *dest, const char *from) {
  
  *size = string_size(from);

  strncpy(dest, from, *size);

  return SUCC;
}