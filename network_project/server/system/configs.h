/*-----------------------------------------------------------------------------------------------------MACROS SERVER MODULE
Macros implemented reg                                                                                                   
//-----------------------------------------------------------------------------------------------------------------------*/
#ifndef CONFIGS_H_
#define CONFIGS_H_

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>

/*---------------------------------------------------------------------STATES SERVER (As for now, only ERROR-flag utilized)
BIT(N)                                    |    15   |    14   |    13   |    12   |    11   |    10   |    9    |    8    |
ERROR HIGH BYTE                           |    -    |    -    |    -    |    -    |    -    |    -    |    -    |    -    |
---------------------------------------------------------------------------------------------------------------------------
BIT(N)                                    |    7    |    6    |    5    |    4    |    3    |    2    |    1    |    0    |
CONSTANT                                  |  ERROR  |    -    |    -    |    -    |    -    |  RECVF  |  SCACC  |  SSONN  |
-------------------------------------------------------------------------------------------------------------------------*/

#define SCONN 0 //  State Connected.
#define SCACC 1                           // State Accept.
#define RECVF 2                           // When set, a request has successfully been revieved from the server.

#define ERROR 7                           /*Something went wrong---------------------------------------------ERROR HANDLING
BIT(N)                                    |    15   |    14   |    13   |    12   |    11   |    10   |    9    |    8    |
ERROR HIGH BYTE                           |    -    |    -    |    -    |  FRERR  |  FWERR  |  SDERR  |  CPERR  |  IFERR  |
---------------------------------------------------------------------------------------------------------------------------
BIT(N)                                    |    7    |    6    |    5    |    4    |    3    |    2    |    1    |    0    |
ERROR HIGH BYTE                           |  PIERR  |  PBERR  |  PDERR  |  PTERR  |  PSERR  |  CAERR  |  CLERR  |  SCERR  |
-------------------------------------------------------------------------------------------------------------------------*/

#define SCERR 0   // Server Connection    Connection lost.
#define CLERR 1   // Client Listening     Failed to listening for clients.
#define CAERR 2   // Client Accept        Failed to accept client.
#define PSERR 3   // Package Size         Package size is corrupted.
#define PTERR 4   // Package Terminate    Package isn't nullterminated.
#define PDERR 5   // Package Delimiter    Corrupted delimiter-format on package.
#define PBERR 6   // Protocol Byte        MSB (one or more bytes) in PROTOCOL isn't set.
#define PIERR 7   // Package Invalid      Package (response) has its VALID-flag cleared (Something went south client-side).
#define IFERR 8   // Iterate Fetch        Failed to fetch an item during iteration (wich should be in place).
#define CPERR 9   // Copy                 Copy is corrupted.
#define SDERR 10  // Switch Default       Defaulted Switch-statement.
#define FWERR 11  // File Write           Failed write to file.
#define FRERR 12  // File Reas            Failed read from file.

/*-----------------------------------------------------------------------------------------------------------------PTOTOCOL
BIT (N)          INDEX (in PROTOCOL)            7         6         5         4         3          2         1        0
---------------------------------------------------------------------------------------------------------------------------
TABLE BYTE         0                       |  MSBIT  |    -    |    -    |    -    |    -    |    -    |  TDVCE  |  TMESG |
---------------------------------------------------------------------------------------------------------------------------
ATTRIBUTE BYTE     1                       |  MSBIT  |  ATTR6  |  ATTR5  |  ATTR4  |  ATTR3  |  ATTR2  |  ATTR1  |  ATTR0 |
---------------------------------------------------------------------------------------------------------------------------
ECHO BYTE          3                       |  MSBIT  |  VALID  |    -    |    -    |    -    |     -   |    -    |  RWBIT |
-------------------------------------------------------------------------------------------------------------------------*/
#define TBIDX 0   // Table Byte Index.
#define ABIDX 1   // Attribute Byte Index.
#define EBIDX 2   // Echo Byte Index.
//---------------------------------------------------------------------------------------------------------------Table Bits
#define TMESG 0   // Table Message Byte
#define TDVCE 1   // Table Device Byte
//-----------------------------------------------------------------------------------------------------------Attribute Bits
#define ATTR0 0
#define ATTR1 1
#define ATTR2 2
#define ATTR3 3
#define ATTR4 4
#define ATTR5 5
#define ATTR6 6
//---------------------------------------------------------------------------------------------------------------Echo Bits
#define RWBIT 0   // Read/Write bit.
#define VALID 6
//------------------------------------------------------------------------------------------------------------------------
#define MSBIT 7   // Most Significant Bit. Always set in bytes belonging to PROTOCOL.
//-----------------------------------------------------------------------------------------------------------------BUFFERS
#define RBUFF 4096  // Receive Buffer.
#define SBUFF 512 // Standard Buffer.
#define TBUFF 22  // Datetime Buffer.
#define POFFS 4   // Package offset.    Size added/reduced for PROTOCOL (and a terminator).
//---------------------------------------------------------------------------------------------------------------DELIMITER
#define DELIM '|' // Delimiter.
#define DMESG 4   // Delemiters Message.
#define DDVCE 3   // Delimiters Device.
//----------------------------------------------------------------------------------------------------------------GRAPHICS
#define FORM_INFO "\t\t\t%s\n"
#define System_Message(info) printf(FORM_INFO, info);
//-------------------------------------------------------------------------------------------------------------------HANDY
#define ARRAY_SIZE(arry) (sizeof(arry)/sizeof(arry[0]))
//--------------------------------------------------------------------------------------------------------------"GRAPHICS"
#define HEADER_FORM "\n%s\n%s\t\t\t%s\n%s\n\n"
#define Header_Border "--------------------------------------------------------------------------------------------------"
#define Render_Header(itm, inf) printf(HEADER_FORM, Header_Border, itm, inf, Header_Border);
//-------------------------------------------------------------------------------------------------------------------DEBUG
#define PrintByte(byte) {for (int i = 7; 0 <= i; i--) {printf("%c", (byte & (1 << i)) ? '1' : '0');} printf("\n");}
#define NUMBFORM "\t\t\tNUMBTEST [%s] %ld\n\n"
//------------------------------------------------------------------------------------------------------------------------

#endif