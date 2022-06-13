/*------------------------------------------------------------------------------------------------------------------------
                                                                                                       CLIENT ERROR MODULE
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/

#include "cerror.h"

static int8_t string_term(char *func, char *strg, uint32_t size_strg) {

	uint8_t result = 0;

	if (!(result = (strg[size_strg - 1] == '\0') ? SUCC : FLEE))
	  Print_String_Fatale(func, strg, "string's not nullterminated.");
	return result;
}

static int8_t string_valid_scan_size(char *strg, uint32_t size_strg, uint32_t size_buff)  {

	uint8_t result = 0;

	if (!(result = (size_strg > 0) ? 1 : 0)) {
	 Print_String_Warning("oops, enter at least one character. try again!");
	 return result;
	} else if (!(result = (size_strg <= size_buff) ? SUCC : FAIL)) {
	 Print_String_Warning("oops, you've reached beyond allowed buffersize. try again.");
	}
	return result;
}

int8_t String_Check(uint8_t check, char *func, char *strg, uint32_t size_strg, uint32_t size_buff) {

	switch(check) {

	case SSTERM:
	  return string_term(func, strg, size_strg);
	break;
	case SVSIZE:
	  return string_valid_scan_size(strg, size_strg, size_buff);
	break;
	default:
	  return FLEE;
	}
	return FLEE;
}
