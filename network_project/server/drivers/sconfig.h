#ifndef DBCONFIG_H_
#define DBCONFIG_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define FLEE -2
#define NBIT -1
#define FAIL 0
#define SUCC 1

/*---------------------------------------------------------------------------------------------------------Request Endbyte
Bit                                 |    7    |    6    |    5    |    4    |    3    |     2    |     1     |     0     |
Constant                            |  RWBIT  |  RTRG2  |  RTRG1  |  RTRG0  |  RMSGE  |   RDVCE  |   RDATA   |   RCONN   |
                                    --------------------------------------------------------------------------------------
                                    |   R/W   |            ACTION           |                   MODEL                    |
                                    --------------------------------------------------------------------------------------

MCONN   Request Connection          Client requests connection business.
MDATA   Request Data                Client requests to fetch data.
MDVCE   Request Device              Client requests interaction with the device.
MMSGE   Request Message             Client requests to write a message. 
RTRGN   Request Trigger(M)          Client request to trigger M on Model N
RWBIT   Request Read/Write          Tells server if request craves either write or read from database.
                                    --------------------------------------------------------------------------------------
RULON   0b00000001                  Request User Login
RUSUP   0b10000001                  Request User Signup
RDTMP   0b00010010                  Request Fetch Temperatures
RDMSG   0b00100010                  Request Fetch Messages
RARED   0b10010100                  Request Activate Device Red (LED)
RABLU   0b10100100                  Request Activate Device Blue (LED)
RAGRN   0b11000100                  Request Activate Device Green (LED)
RWMSG   0b10011000                  Request Write Message



#define RUSUP 0b10000001 //         Request Write User (sign up)
#define RULOG 0b00000001 //         Request Read Users (login)

#define RDTMP 0b00010010 //         Request Read Temperature (only data at the moment)

#define RARED 0b10010100 //         Request Activate Device Red (LED)
#define RABLU 0b10100100 //         Request Activate Device Blue (LED)
#define RAGRN 0b11000100 //         Request Activate Device Green (LED)

#define RWMSG 0b10001000 //         Request Write Message
#define RWMSG 0b00001000 //         Request Read Messages

                                    ------------------------------------------------------------------------------------*/
#define RCONN 0
#define RDATA 1
#define RDVCE 2
#define RMSGE 3
#define RTRG0 4
#define RTRG1 5
#define RTRG2 6
#define RWBIT 7
//------------------------------------------------------------------------------------------------------------------------
#define LNIBB 4
#define HNIBB 8
//------------------------------------------------------------------------------------------------------------------------
#define DELIM '|'       //          Delimiter
#define DCLNT 3         //          Delimiters Client
#define DSMPL 3         //          Delimiters Sample
#define DDVCE 4         //          Delimiters Device
#define DMSGE 5         //          Delimiters Message
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