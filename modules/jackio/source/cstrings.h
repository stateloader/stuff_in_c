#ifndef CSTRINGS__H_
#define CSTRINGS__H_

#ifndef BUFF_SIZE_LIMIT
#define BUFF_SIZE_LIMIT 4019
#endif

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

void buffer_flush(size_t size_buff, char *data_buff);

size_t string_size(size_t size_data_buff, const char *data_buff);
size_t string_copy(size_t size_copy_buff, char *copy_buff, const char *from_buff);
size_t string_ccat(size_t size_dest_buff, char *dest_buff, const char *with_buff);
int8_t string_comp(size_t size_comp_buff, const char *str1, const char *str2);

#endif
