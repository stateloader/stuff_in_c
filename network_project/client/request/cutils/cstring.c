/*------------------------------------------------------------------------------------------------------------------------
                                                                                                      CLIENT STRING DRIVER
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cerror.h"
#include "cconfig.h"
#include "cstring.h"

uint32_t string_size(char *string, uint32_t buffer_size)  {
  for (size_t i = 0; i < buffer_size - 1; i++) {
    if (string[i] == '\0') 
      return (i + 1);
  }
  return 0;
}

int8_t string_comp(char *str1, const char *str2, uint32_t comp_buff) {

  uint32_t match = 0;
  for (uint32_t i = 0; i < comp_buff; i++)
    match += (str1[i] == str2[i]) ? 1 : 0;
  if (match == comp_buff)
    return SUCC;
  return FAIL;
}
