#ifndef DBCONFIG_H_
#define DBCONFIG_H_

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>

#define SUCC 1
#define FAIL 0
/*------------------------------------------------------------------------------------------------------------------------
                                                                                                MACRO KEYS, DATBASE MODULE
info info info
------------------------------------------------------------------------------------------------------------------------*/
#define PCLNT "resources/client.dat"    // path client          - relative path to .dat-file storing clientdata.
#define PSMPL "resources/sample.dat"    // Path sample          - relative path to .dat-file storing sampledata.
#define PMSGE "resources/message.dat"   // Path message         - relative path to .dat-file storing messagedata.
#define PDVCE "resources/device.dat"    // Path device          - relative path to .dat-file storing devicedata.
/*---------------------------------------------------------------------------------------------------------BYTE: "REQUEST"

bit                     |    7    |    6    |    5    |    4    |    3    |     2    |     1     |     0     |
constant                |  RWBIT  |    -    |    -    |    -    |    -    |   MMSGE  |   MSMPL   |   MCLNT   |
                                                                                                                        */
#define RWBIT 7         // R/W bit              - mapped to 8:th bit R/W-bit in byte "request"-byte.

#define RINIT 0         // Read Init            - flag to run read-logic.
#define WINIT 1         // Write Init           - flag to run write-logic.

#define MCLNT 0         // Model Client         - flag to deal with Client-data.
#define MSMPL 1         // Model Sample         - flag to deal with Sample-data.
#define MMSGE 2         // Model Message        - flag to deal with Message-data
#define MDVCE 3         // Model Device         - flag to deal with Device-data.

//------------------------------------------------------------------------------------------------------------------------

#define DELIM '|'       // Delimiter            - "pipe"-char used as placehlder throughout the program. 
#define CCLNT 2         // Count Client         - "interval" of delims, (N) members, for each client row.
#define CSMPL 2         // Count Sample         - "interval" of delims, (N) members, for each sample row.
#define CMSGE 4         // Count Message        - "interval" of delims, (N) members, for each message row.
#define CDVCE 3
//------------------------------------------------------------------------------------------------------------------------

#define FBUFF 4096      // File Buffer          - max allowed size of a file buffer.
#define MBUFF 512       // Message Buffer       - max allowed size of a message buffer.
#define DBUFF 64        // Data Buffer          - max allowed soze of a data buffer.
#define TBUFF 24        // Time Buffer          - max allowed soze of a datetime buffer.

//------------------------------------------------------------------------------------------------------------------------

#define SUSER 0
#define SPASS 1
#define STEMP 0
#define SDTME 1
//-------------------------------------------------------------------------------------------------------------------OTHER
#define PrintByte(msk) {for (int i = 7; 0 <= i; i--) {printf("%c", (msk & (1 << i)) ? '1' : '0');} printf("\n");}
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

#endif





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
------------------------------------------------------------------------------------------------------------------------*/