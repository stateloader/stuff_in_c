/*------------------------------------------------------------------------------------------------------------------------
                                                                                                MACRO KEYS, REQUEST_MODULE
info info info
------------------------------------------------------------------------------------------------------------------------*/
#ifndef CCONFIG_H_
#define CCONFIG_H_

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
/*---------------------------------------------------------------------------------------------------------Request Endbyte
Bit                                 |    7    |    6    |    5    |    4    |    3    |     2    |     1     |     0     |
Constant                            |  RWBIT  |  RTDT2  |  RTDT1  |  RTDT0  |  RMSGE  |   RDVCE  |   RDATA   |   RCONN   |
                                    --------------------------------------------------------------------------------------
MCONN   Request Connection          Set flags server to init connection stuff (i.e user login/signup).
MDATA   Request Data                Set flags server to init data/read (from database) stuff.
MDVCE   Request Device              Set flags server to init interaction with device stuff.
MMSGE   Request Message             Set flags server to init message stuff.
RTDT(N) Request To Do This          Bit 4 to 6 used for flagging michallenous to the server.
RWBIT   Request Read/Write          Set flags server it's a writing (to database) errant, cleared reading from it.
                                    -----------------------------------------------------------------------------------*/
#define DELIM '|'
#define FAIL 0
#define SUCC 1
//------------------------------------------------------------------------------------------------------------------------
#define FBUFF 4096
#define SBUFF 512
#define TBUFF 32
//--------------------------------------------------------------------------------------------------------------"Graphics"
#define HEADER_FORM "%s\n%s\t\t%s\n%s\n\n"

#define Header_Bord "----------------------------------------------------------------------------------------------------"
#define Render_Header(itm, inf) printf(HEADER_FORM, Header_Bord, itm, inf, Header_Bord);

#define SYSTEM_FORM "  %s\n"
#define System_Message(sys) (printf(SYSTEM_FORM, sys))
//-------------------------------------------------------------------------------------------------------------some check
#define PrintByte(msk) {for (int i = 7; 0 <= i; i--) {printf("%c", (msk & (1 << i)) ? '1' : '0');} printf("\n");}

#define check_delm(str, len) (str[len - 1] == DELIM)
#define check_rdfm(str, len) (str[len - 3] == DELIM)
#define check_size(scn, buf) (scn < buf - 1) 
#define check_term(scn, len) (scn[len - 1] == '\0')
//-------------------------------------------------------------------------------------------------------------------other
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

#endif