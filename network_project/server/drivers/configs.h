#ifndef CONFIGS_H_
#define CONFIGS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

/*---------------------------------------------------------------------------------------------------------------Task Byte
Bit                                 |    7    |    6    |    5    |    4    |    3    |     2    |     1     |     0     |
Constant                            |  _MDEF  |    -    |    -    |    -    |    -    |     -    |   TDVCE   |   TMESG   |
------------------------------------------------------------------------------------------------------------------------*/              
#define TMESG 0      // Task Message
#define TDVCE 1      // Task Device
/*------------------------------------------------------------------------------------------------------------Execute Byte
Bit                                 |    7    |    6    |    5    |    4    |    3    |     2    |     1     |     0     |
Constant                            |  _MDEF  |  RWBIT  |  EXEC5  |  EXEC4  |  EXEC3  |   EXEC2  |   EXEC1   |   EXEC0   |
------------------------------------------------------------------------------------------------------------------------*/
#define EXEC0 0
#define EXEC1 1
#define EXEC2 2
#define EXEC3 3
#define EXEC4 4
#define EXEC5 5
#define RWBIT 6
//------------------------------------------------------------------------------------------------------------------------
#define POFFS 4
//------------------------------------------------------------------------------------------------------------------------
#define DELIM '|'
#define FAIL 0
#define SUCC 1
//------------------------------------------------------------------------------------------------------------------------
#define FBUFF 4096      //          File Buffer
#define SBUFF 512       //          Scan Buffer
#define PBUFF 64        //          Path Buffer
#define TBUFF 24        //          Time (DateTime) Buffer
//--------------------------------------------------------------------------------------------------------------"Graphics"
#define HEADER_FORM "%s\n%s\t\t%s\n%s\n\n"

#define Header_Bord "----------------------------------------------------------------------------------------------------"
#define Render_Header(itm, inf) printf(HEADER_FORM, Header_Bord, itm, inf, Header_Bord);

#define SYSTEM_FORM "  %s\n"
#define System_Message(sysmesg) printf(SYSTEM_FORM, sysmesg);
//-------------------------------------------------------------------------------------------------------------some checks
#define check_delm(str, len) (str[len - 1] == DELIM)
#define check_size(scn, buf) (scn < buf - 1) 
#define check_term(scn, len) (scn[len - 1] == '\0')
#define check_tedl(str, len) (str[len - 3] == '|')
#define check_cnum(nm0, nm1) (nm0 == nm1)
#define check_endf(str, len) (str[len - 2] == '|' && str[len - 1] == '\0')
//--------------------------------------------------------------------------------------------------------------------bits
#define fetch_endb(byt, str, len) (byt = str[len - 2])
#define parse_rewr(msk) (msk & (1 << 7))
//-------------------------------------------------------------------------------------------------------------------other
#define PrintByte(msk) {for (int i = 7; 0 <= i; i--) {printf("%c", (msk & (1 << i)) ? '1' : '0');} printf("\n");}
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))
#define Print_Numb(num, not) printf("TEST---NUMBER: %d ---NOTE %s\n", num, not);

#endif