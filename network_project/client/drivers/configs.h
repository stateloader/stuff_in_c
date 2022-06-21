/*----------------------------------------------------------------------------------------------------MACROS CLIENT MODULE
info info info
------------------------------------------------------------------------------------------------------------------------*/
#ifndef CCONFIG_H_
#define CCONFIG_H_

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
/*---------------------------------------------------------------------------------------------------------------Task Byte
Bit                                 |    7    |    6    |    5    |    4    |    3    |     2    |     1     |     0     |
Constant                            |    -    |    -    |    -    |    -    |    -    |     -    |   TDVCE   |   TMESG   |
------------------------------------------------------------------------------------------------------------------------*/              
#define TMESG 0      // Task Message
#define TDVCE 1      // Task Device
/*------------------------------------------------------------------------------------------------------------Execute Byte
Bit                                 |    7    |    6    |    5    |    4    |    3    |     2    |     1     |     0     |
Constant                            |    -    |  RWBIT  |  EXEC5  |  EXEC4  |  EXEC3  |   EXEC2  |   EXEC1   |   EXEC0   |
------------------------------------------------------------------------------------------------------------------------*/
#define EXEC0 0
#define EXEC1 1
#define EXEC2 2
#define EXEC3 3
#define EXEC4 4
#define EXEC5 5
#define RWBIT 6
//------------------------------------------------------------------------------------------------------------------------
#define DELIM '|'
#define FAIL 0
#define SUCC 1
//------------------------------------------------------------------------------------------------------------------------
#define FBUFF 4096
#define SBUFF 512
#define TBUFF 32
//--------------------------------------------------------------------------------------------------------------"Graphics"
#define HEADER_FORM "%s\n%s\n\t\t%s\n%s\n\n"

#define Header_Bord "----------------------------------------------------------------------------------------------------"
#define Render_Header(itm, inf) printf(HEADER_FORM, Header_Bord, itm, inf, Header_Bord);

#define SYSTEM_FORM "  %s\n"
#define System_Message(sys) (printf(SYSTEM_FORM, sys))
//-------------------------------------------------------------------------------------------------------------some check
#define check_delm(str, len) (str[len - 1] == DELIM)
#define check_size(scn, buf) (scn < buf - 1) 
#define check_term(scn, len) (scn[len - 1] == '\0')
//----------------------------------------------------------------------------------------------------------------Bit stuff
#define PrintByte(msk) {for (int i = 7; 0 <= i; i--) {printf("%c", (msk & (1 << i)) ? '1' : '0');} printf("\n");}
//-------------------------------------------------------------------------------------------------------------------other
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))
#define Print_Numb(num, not) printf("TEST---NUMBER: %d ---NOTE %s\n", num, not);

#endif