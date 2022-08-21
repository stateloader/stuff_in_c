#ifndef CSTRINGS_H_
#define CSTRINGS_H_

#ifndef CST_MAX_BUFF
#define CST_MAX_BUFF 4019
#endif

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

#define CST_Error_Mesg(func, mesg) fprintf(stdout, "[ERROR] %s, %s %s, \"%s\", \"%s\"\n", __FILE__, __TIME__, __DATE__, func, mesg);

void buffer_flush(char *strg, size_t size_strg_buff);

size_t string_size(const char *strg, size_t size_strg);
size_t string_copy(char *copy_buff, size_t size_buff, const char *from);
size_t string_ccat(char *dest_buff, size_t size_buff, const char *with);
size_t string_mcat(char *dest_buff, size_t size_buff, const char **from);
int8_t string_comp(const char *str1, const char *str2, size_t size_comp);
char *string_heap(const char *from, size_t *size_heap);

#define String_Head(strg, size)\
				printf("\n\"%s\"\n", strg);\
				printf("--------------------------------------------------------------------------------------------------\n");\
				printf("Index\tHex\tDec\tOct\tBin\t\tChr\tDesc                    String Size %ld\n", size);\
				printf("--------------------------------------------------------------------------------------------------\n");

#define String_Data(index, table, byte)\
				fprintf(stdout, "%ld\t%s\t%s\t%s\t%s\t%s\t%s\n",\
				index, table[byte].display_hex, table[byte].display_dec, table[byte].display_oct,\
				table[byte].display_bin, table[byte].display_chr, table[byte].display_key);

#define array_size(arry) (sizeof(arry)/sizeof(arry[0]))

#endif
