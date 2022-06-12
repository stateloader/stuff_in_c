/*------------------------------------------------------------------------------------------------------------------------
                                                                                                      CLIENT STRING DRIVER
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cconfig.h"
#include "cstring.h"

static void string_term(char *string, uint32_t size) {

	if (!check_term(string, size)) {
    printf("Not terminated\n");
    exit(EXIT_FAILURE);
  }
}

uint32_t string_size(char *string, uint32_t buffer_size) {

  uint32_t string_size = strnlen(string, buffer_size - 1);
  string[string_size - 1] = '\0';
  return string_size;
}

uint8_t string_comp(char *str1, const char *str2, uint32_t comp_length) {

  uint32_t match = 0;
  for (uint32_t i = 0; i < comp_length; i++)
    match += (str1[i] == str2[i]) ? 1 : 0;
  if (match == comp_length)
    return SUCC;
  return FAIL;
}
