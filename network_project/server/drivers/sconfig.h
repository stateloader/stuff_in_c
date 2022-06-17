#ifndef DBCONFIG_H_
#define DBCONFIG_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define FLEE -2
#define NACT -1
#define FAIL 0
#define SUCC 1
/*---------------------------------------------------------------------------------------------------------Request Endbyte
Bit                                 |    7    |    6    |    5    |    4    |    3    |     2    |     1     |     0     |
Constant                            |  RWBIT  |  RACT2  |  RACT1  |  RACT0  |  RMSGE  |   RDVCE  |   RDATA   |   RCONN   |
                                    --------------------------------------------------------------------------------------
MCONN   Request Connection          Client requests connection business.
MDATA   Request Data                Client requests to fetch data.
MDVCE   Request Device              Client requests interaction with the device.
MMSGE   Request Message             Client requests to write a message. 
RACTN   Request Action (N)          Client request "Action" (with <bit>) Emaxple: RDVCE - turn on red led).
RWBIT   Request Read/Write          Tells server if request craves either write or read from database.
                                    ------------------------------------------------------------------------------------*/
#define RCONN 0
#define RDATA 1
#define RDVCE 2
#define RMSGE 3

#define RTDT0 4
#define RTDT1 5
#define RTDT2 6
#define RWBIT 7

#define LNIBB 4
#define HNIBB 8

//------------------------------------------------------------------------------------------------------------------------
#define DELIM '|'       //          Delimiter
#define DCLNT 3         //          Delimiters Client
#define DSMPL 3         //          Delimiters Sample
#define DDVCE 4         //          Delimiters Device
#define DMSGE 5         //          Delimiters Message
//------------------------------------------------------------------------------------------------------------------------
#define FBUFF 4096      //          desc
#define RBUFF 4096      //          desc
#define SBUFF 512       //          desc
#define TBUFF 21        //          desc
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
#define check_tedl(str, len) (str[len - 3] == '|')
//--------------------------------------------------------------------------------------------------------------------bits
#define fetch_endb(byt, str, len) (byt = str[len - 2])
#define parse_rewr(msk) (msk & (1 << 7))
//-------------------------------------------------------------------------------------------------------------------other
#define PrintByte(msk) {for (int i = 7; 0 <= i; i--) {printf("%c", (msk & (1 << i)) ? '1' : '0');} printf("\n");}
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))
#define Print_Numb(num, not) printf("TEST---NUMBER: %d ---NOTE %s\n", num, not);
#endif


/*
#define TESTSTRFORM "\nstring -- %s -- %s\n\n"
#define System_Print_String(str, inf) printf(TESTSTRFORM, str, inf)
#define Print_Numb(num, not) printf("TEST---NUMBER: %d ---NOTE %s\n", num, not);
#define Print_Strg(str, not) printf("TEST---STRING: %s ---NOTE %s\n", str, not);
#define Print_Byte(msk) {for (int i = 7; 0 <= i; i--) {printf("%c", (msk & (1 << i)) ? '1' : '0');} printf("\n");}
*/


/*
#define RULON 0b00000001 //         Recieved User Login
#define RUSUP 0b10000001 //         Recieved User Signup
#define RDTMP 0b00010010 //         Recieved Fetch Temperature
#define RDMSG 0b00100010 //         Recieved Fetch Messages
#define RARED 0b10010100 //         Recieved Activate Device Red (LED)
#define RABLU 0b10100100 //         Recieved Activate Device Blue (LED)
#define RAGRN 0b11000100 //         Recieved Activate Device Green (LED)
#define RWMSG 0b10011000 //         Recieved Write Message
*/