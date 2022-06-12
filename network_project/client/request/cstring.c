/*------------------------------------------------------------------------------------------------------------------------
                                                                                                             STRING DRIVER
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cstring.h"

static void string_term(char *string, size_t size) {

	if (!check_term(string, size)) {
    printf("ERROR TERM -- string %s not nullterminated.\n", string);
    exit(EXIT_FAILURE);
  }
}

size_t string_size(char *string, size_t buffer_size) {

  size_t size = strnlen(string, buffer_size - 1);

  string[size - 1] = '\0';
  string_term(string, size);

  return size;
}
