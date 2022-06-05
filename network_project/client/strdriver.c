/*------------------------------------------------------------------------------------------------------------------------
                                                                                                             STRING DRIVER
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strdriver.h"

static void string_term(char *string, size_t size) {

	if (!check_term(string, size)) {
    printf("ERROR TERM -- string %s not nullterminated.\n", string);
    exit(EXIT_FAILURE);
  }
}

size_t string_size(char *string) {

  size_t size = strnlen(string, MAX_BUFFER - 1);

  if (size >= MAX_BUFFER - 1) {
    printf("ERROR SIZE  -- string %s would overflow the buffer.\n", string);
    exit(EXIT_FAILURE);
  }
  return size;
}

void string_copy(char *dest, char *from, size_t size) {

  if (!strncpy(dest, from, size)) {
    printf("ERROR COPY  -- string %s wasn't properly copied.\n", from);
    exit(EXIT_FAILURE);
  }
  string_term(dest, size);
}

void string_comp(char *dest, char *from, size_t size) {

  if (!strncmp(dest, from, size) == 0) {
    printf("ERROR COMP  -- string %s and %s doesn't compare.\n", dest, from);
    exit(EXIT_FAILURE);

  } else if (string_size(dest) && string_size(from) != size) {
		printf("ERROR DIFF  -- string %s and %s are of different sizes.\n", dest, from);
    exit(EXIT_FAILURE);
  }
  string_term(dest, size);
}
void string_merge(char *dest, char *with) {

  size_t dest_size = string_size(dest);
  size_t with_size = string_size(with);
  size_t mergesize = dest_size + with_size;

  if (mergesize >= MAX_BUFFER - 1) {
    printf("ERROR MERGE -- merge of string %s and %s would overflow the buffer", dest, with);
    exit(EXIT_FAILURE);
  }

  strncat(dest, with, with_size);
  string_term(dest, mergesize);
}

void string_test(char *string, size_t size) {

  for (size_t i = 0; i < size; i++) {
    if (string[i] == '\n')
      printf("[%ld] - NEWL\n", i);
    else if (string[i] == '\0')
      printf("[%ld] - NULL\n", i);
    else {
      printf("[%ld] - %c\n", i, string[i]);
    }
  }
}
