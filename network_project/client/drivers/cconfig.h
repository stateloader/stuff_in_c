/*------------------------------------------------------------------------------------------------------------------------
                                                                                                MACRO KEYS, REQUEST_MODULE
info info info
------------------------------------------------------------------------------------------------------------------------*/
#ifndef CCONFIG_H_
#define CCONFIG_H_
#include <string.h>
#include <stdio.h>
/*---------------------------------------------------------------------------------------------------------Request Endbyte
Bit                                 |    7    |    6    |    5    |    4    |    3    |     2    |     1     |     0     |
Constant                            |  RWBIT  |  RTDT2  |  RTDT1  |  RTDT0  |  RMSGE  |   RDVCE  |   RDATA   |   RCONN   |
                                    --------------------------------------------------------------------------------------
MCONN   Request Connection          Set flags server to init connection stuff (i.e user login/signup).
MDATA   Request Data                Set flags server to init data/fetch (from database) stuff.
MDVCE   Request Device              Set flags server to init interaction with device stuff.
MMSGE   Request Message             Set flags server to init message stuff.
RTDT(N) Request To Do This          Bit 4 to 6 used for flagging michallenous to the server.
RWBIT   Request Read/Write          Set flags server it's a writing (to database) errant, cleared reading from it.
                                    -----------------------------------------------------------------------------------*/
#define RULON 0b00000001 //         Request User Login
#define RUSUP 0b10000001 //         Request User Signup
#define RDTMP 0b00010010 //         Request Fetch Temperature
#define RDMSG 0b00100010 //         Request Fetch Messages
#define RARED 0b10010100 //         Request Activate Device Red (LED)
#define RABLU 0b10100100 //         Request Activate Device Blue (LED)
#define RAGRN 0b11000100 //         Request Activate Device Green (LED)
#define RWMSG 0b10011000 //         Request Write Message
//------------------------------------------------------------------------------------------------------------------------
#define FAIL 0
#define SUCC 1
//------------------------------------------------------------------------------------------------------------------------
#define LOGN 0
#define SIGU 1
#define TEMP 0
#define MESG 1
#define DRED 0
#define DBLU 1
#define DGRN 2
//------------------------------------------------------------------------------------------------------------------------
#define FLEE -2
#define DONE -1
#define MAIN 0
//------------------------------------------------------------------------------------------------------------------------
#define RBUFF 4096
#define CBUFF 512
#define TBUFF 21
//--------------------------------------------------------------------------------------------------------------"Graphics"
#define HEADER_FORM "%s\n%s\t\t%s\n%s\n\n"

#define Header_Bord "----------------------------------------------------------------------------------------------------"
#define Render_Header(itm, inf) printf(HEADER_FORM, Header_Bord, itm, inf, Header_Bord);

#define SYSTEM_FORM "\n\t%s\n\n"
#define System_Message(sysmesg) printf(SYSTEM_FORM, sysmesg);

#define TESTSTRFORM "\nstring -- %s -- %s\n\n"
#define System_Print_String(str, inf) printf(TESTSTRFORM, str, inf)
//-------------------------------------------------------------------------------------------------------------some checks
#define check_delm(str, len) (str[len - 1] == DELIM)
#define check_rdfm(str, len) (str[len - 3] == DELIM)
#define check_size(scn, buf) (scn < buf - 1) 
#define check_term(scn, len) (scn[len - 1] == '\0')

#define PrintByte(msk) {for (int i = 7; 0 <= i; i--) {printf("%c", (msk & (1 << i)) ? '1' : '0');} printf("\n");}
//-------------------------------------------------------------------------------------------------------------------other
#define DELIM '|'
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

#endif