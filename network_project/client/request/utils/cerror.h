/*------------------------------------------------------------------------------------------------------------------------
                                                                                                       CLIENT ERROR MACROS
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/

#ifndef CERROR_H_
#define CERROR_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "cconfig.h"

#define SSTERM 0     // String terminated.
#define SVSIZE 1     // String Valid input size.

#define STRERRFORM "STRING ERROR---in func '%s', string '%s' %s"
//-------------------------------------------------------------------------------------------------------------CHECK CODES

//this is for the idiot.
#define STRING_FLEE_FORMAT "\n\t\tSTRING FAILURE in function '%s', string '%s' %s\n"
#define Print_String_Fatale(func, strg, mesg) printf(STRING_FLEE_FORMAT, func, strg, mesg)

//this is for the user.
#define STRING_WARN_FORMAT "\n\t\t%s\n\n"
#define Print_String_Warning(mesg) printf(STRING_WARN_FORMAT, mesg)

int8_t String_Check(uint8_t check, char *func, char *strg, uint32_t size_strg, uint32_t size_buff);

#endif