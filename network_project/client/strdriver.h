#ifndef STRINGDRIVER_H_
#define STRINGDRIVER_H_

#include <stddef.h>
#include <stdint.h>

#define MAX_BUFFER 4096

#define check_term(str, len) (str[len - 1] == '\0')

void string_test(char *string, size_t size);
size_t string_size(char *string);
void string_copy(char *dest, char *from, size_t size);
void string_comp(char *dest, char *from, size_t size);
void string_merge(char *dest, char *with);

#endif
