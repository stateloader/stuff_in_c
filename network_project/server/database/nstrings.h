#ifndef NSTRINGS_H_
#define NSTRINGS_H_

#include <stddef.h>
#include <stdint.h>

#define MAX_STR_SIZE 4096

#define VALID 0
#define ABORT 1
#define FATAL 2

#define STRING_ERROR_FORMAT "STRING ERROR----\n\nFUNC - %s\nNOTE - %s\n\n'%s'\n\nSTRING ERROR----\n\n"     
#define String_Error_Message(errfunc, errnote, errstr) printf(STRING_ERROR_FORMAT, errfunc, errnote, errstr)

#define check_term(str, size) (str[size - 1] == '\0')

size_t string_size(const char *string);
uint8_t string_copy(size_t *size, char *dest, const char *from);

#endif