#ifndef STRINGDRIVER_H_
#define STRINGDRIVER_H_

#include <stddef.h>
#include <stdint.h>

#define check_term(str, len) (str[len - 1] == '\0')

void string_test(char *string, size_t size);
size_t string_size(char *string, size_t buffer_size);

#endif
