#ifndef DBCONFIG_H_
#define DBCONFIG_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define SUCC 1
#define FAIL 0
/*------------------------------------------------------------------------------------------------------------------------
                                                                                                MACRO KEYS, DATBASE MODULE
info info info
------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------Request Endbyte
Bit                                 |    7    |    6    |    5    |    4    |    3    |     2    |     1     |     0     |
Constant                            |  RWBIT  |  RTDT2  |  RTDT1  |  RTDT0  |  RMSGE  |   RDVCE  |   RDATA   |   RCONN   |
                                    --------------------------------------------------------------------------------------
MCONN   Request Connection          Get flags server to init connection stuff (i.e user login/signup).
MDATA   Request Data                Get flags server to init data/fetch (from database) stuff.
MDVCE   Request Device              Get flags server to init interaction with device stuff.
MMSGE   Request Message             Get flags server to init message stuff.
RTDTN   Request To Do This (N)      Bit 4 to 6 used for flagging stuff to the server.
RWBIT   Request Read/Write          Get flags server it's a writing (to database) errant, cleared reading from it.
------------------------------------------------------------------------------------------------------------------------*/
#define RULO 0b00000001 //          Request User Login
#define RUSU 0b10000001 //          Request User Signup
#define RDTP 0b00010010 //          Request Fetch Temperature
#define RDMG 0b00100010 //          Request Fetch Messages
#define RADR 0b10010100 //          Request Activate Device Red (LED)
#define RADB 0b10100100 //          Request Activate Device Blue (LED)
#define RADG 0b11000100 //          Request Activate Device Green (LED)
#define RWMG 0b10011000 //          Request Write Message
//------------------------------------------------------------------------------------------------------------------------
#define DELIM '|'       //          Delimiter
#define DCLNT 2         //          Delimiters Client
#define DSMPL 2         //          Delimiters Sample
#define DMSGE 4         //          Delimiters Message
#define DDVCE 3         //          Delimiters Device
//------------------------------------------------------------------------------------------------------------------------
#define FBUFF 4096      //          desc
#define RBUFF 4096      //          desc
#define SBUFF 512       //          desc
#define TBUFF 21        //          desc
//------------------------------------------------------------------------------------------------------------------------
#define SUSER 0
#define SPASS 1
#define STEMP 0
#define SDTME 1
//--------------------------------------------------------------------------------------------------------------"Graphics"
#define HEADER_FORM "%s\n%s\t\t%s\n%s\n\n"

#define Header_Bord "----------------------------------------------------------------------------------------------------"
#define Render_Header(itm, inf) printf(HEADER_FORM, Header_Bord, itm, inf, Header_Bord);

#define SYSTEM_FORM "\n\t\t%s\n\n"
#define System_Message(sysmesg) printf(SYSTEM_FORM, sysmesg);
//-------------------------------------------------------------------------------------------------------------some checks
#define check_delm(str, len) (str[len - 1] == DELIM)
#define check_size(scn, buf) (scn < buf - 1) 
#define check_term(scn, len) (scn[len - 1] == '\0')
//-------------------------------------------------------------------------------------------------------------------OTHER
#define TESTSTRFORM "\nstring -- %s -- %s\n\n"
#define System_Print_String(str, inf) printf(TESTSTRFORM, str, inf)
#define PrintByte(msk) {for (int i = 7; 0 <= i; i--) {printf("%c", (msk & (1 << i)) ? '1' : '0');} printf("\n");}
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))
#define Print_Numb(num, not) printf("TEST---NUMBER: %d ---NOTE %s\n", num, not);
#define Print_Strg(str, not) printf("TEST---STRING: %s ---NOTE %s\n", str, not);
#define Print_Byte(msk) {for (int i = 7; 0 <= i; i--) {printf("%c", (msk & (1 << i)) ? '1' : '0');} printf("\n");}

#endif