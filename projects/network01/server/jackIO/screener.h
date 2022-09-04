#ifndef SCREENER__H_
#define SCREENER__H_

#ifndef BUFF_SIZE_LIMIT
#define BUFF_SIZE_LIMIT 4019
#endif

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

#define String_Head(strg, size)\
				printf("\n\"%s\"\n", strg);\
				printf("--------------------------------------------------------------------------------------------------\n");\
				printf("Index\tHex\tDec\tOct\tBin\t\tChr\tDesc                    String Size %ld\n", size);\
				printf("--------------------------------------------------------------------------------------------------\n");

#define String_Data(index, table, byte)\
				fprintf(stdout, "%ld\t%s\t%s\t%s\t%s\t%s\t%s\n",\
				index, table[byte].display_hex, table[byte].display_dec, table[byte].display_oct,\
				table[byte].display_bin, table[byte].display_chr, table[byte].display_key);

void screen_driver(const char *string);

#endif
