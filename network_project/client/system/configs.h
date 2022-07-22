/*-----------------------------------------------------------------------------------------------------MACROS CLIENT MODULE
Macros implemented reg                                                                                                   
//-----------------------------------------------------------------------------------------------------------------------*/
#ifndef CONFIGS_H_
#define CONFIGS_H_

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

/*------------------------------------------------------------------------------------------------------------STATES CLIENT
BIT(N)                                    |    7    |    6    |    5    |    4    |    3    |    2    |    1    |    0    |
CONSTANT                                  |  ERROR  |    -    |    -    |    -    |  SRECV  |  SREQT  |  SCOMM  |  SCONN  |
-------------------------------------------------------------------------------------------------------------------------*/
#define SCONN 0                           // State Connected.
#define SCOMM 1                           // State Command.
#define SREQT 2                           // State Request.
#define SRECV 3                           // State Receive.

#define ERROR 7                           /*Something went wrong---------------------------------------------ERROR HANDLING
BIT(N)                                    |    15   |    14   |    13   |    12   |    11   |    10   |    9    |    8    |
ERROR HIGH BYTE                           |  SDERR  |    -    |  MMERR  |  IVERR  |  DCERR  |  PBERR  |  RRERR  |  RSERR  |
---------------------------------------------------------------------------------------------------------------------------
BIT(N)                                    |    7    |    6    |    5    |    4    |    3    |    2    |    1    |    0    |
ERROR LOW BYTE                            |  SDERR  |  TPERR  |  IIERR  |  PDERR  |  PTERR  |  PSERR  |  SCERR  |  SSERR  |
-------------------------------------------------------------------------------------------------------------------------*/
#define SSERR 0                           // Failed to create create client-socket.                         
#define SCERR 1                           // Failed to connect to server.
#define PSERR 2                           // Package size error, sizes between sent and created doesn't match. 
#define PTERR 3                           // Package (not) terminated error, package isn't nullterminated.
#define PDERR 4                           // The supposed amount the entry's delimiter-constant supposed to be is wrong.
#define IIERR 5                           // Failed to fetch an item (wich should be in place).
#define CPERR 6                           // Copy Failure.
#define SDERR 7                           // A given switch-statment has reach default (for some reason).
#define RSERR 8                           // Failed to send package, size of size_pack and size_send differ.
#define RRERR 9                           // Failed to receive package, size of size_pack and size_recv differ.
#define PBERR 10                          // Protocol Byte wrong format.
#define DCERR 11                          // Delimitier count corrupted.
#define IVERR 12                          // Server has cleared VALID-flag.
#define MMERR 13                          // Failed to allocate memory for table.

/*-----------------------------------------------------------------------------------------------------------------PTOTOCOL
The protocol, throughout the comments referred to as 'PROTOCOL' consist of 3 bytes (and a NULL-terminator). This protocol
will be attached at the end of every package from both the server and the client during transmissions. For the moment it's
just possble to write/read regarding comments and the device. Much logic across the program is mostly in place for making
it easier to scale things up down the road.

BIT (N)          INDEX (in PROTOCOL)            7         6         5         4         3          2         1        0
---------------------------------------------------------------------------------------------------------------------------
TABLE BYTE         0                       |  UNBIT  |    -    |    -    |    -    |    -    |    -    |  TDVCE  |  TMESG |
---------------------------------------------------------------------------------------------------------------------------
ATTRIBUTE BYTE     1                       |  UNBIT  |  ATTR6  |  ATTR5  |  ATTR4  |  ATTR3  |  ATTR2  |  ATTR1  |  ATTR0 |
---------------------------------------------------------------------------------------------------------------------------
ECHO BYTE          2                       |  UNBIT  |  VALID  |    -    |    -    |    -    |     -   |    -    |  RWBIT |
-------------------------------------------------------------------------------------------------------------------------*/
#define UNBIT 7                           // Most Significant Bit. Always set, constant used for error-checking/formatting.

#define TBIDX 0                           // Table Byte Index.
#define ABIDX 1                           // Attribute Byte Index.
#define EBIDX 2                           // Echo Byte Index.
//---------------------------------------------------------------------------------------------------------------Table Bits
#define TMESG 0                           // Table Message Byte
#define TDVCE 1                           // Table Device Byte
//-----------------------------------------------------------------------------------------------------------Attribute Bits
#define ATTR0 0
#define ATTR1 1
#define ATTR2 2
#define ATTR3 3
#define ATTR4 4
#define ATTR5 5
#define ATTR6 6
//---------------------------------------------------------------------------------------------------------------Echo Bits
#define RWBIT 0                           // Read/Write bit.
#define VALID 6
//-----------------------------------------------------------------------------------------------------------------BUFFERS
#define RBUFF 4096                        // Receive Buffer
#define SBUFF 512                         // Standard (Input) Buffer.
#define TBUFF 22                          // Datetime Buffer
#define POFFS 4                           // Package offset. Size added/reduced for PROTOCOL (and a terminator).
//---------------------------------------------------------------------------------------------------------------DELIMITER
#define DELIM '|'                         // Delimiter.
#define DMESG 4                           // Delemiters (in) Message.
#define DDVCE 3                           // Delimiters (in) Device.
//----------------------------------------------------------------------------------------------------------------GRAPHICS
#define FORM_INFO "\t\t\t%s\n"
#define System_Message(info) printf(FORM_INFO, info);

#define HEADER_FORM "\n%s\n%s\t\t\t%s\n%s\n\n"
#define Header_Border "--------------------------------------------------------------------------------------------------"
#define Render_Header(item, info) printf(HEADER_FORM, Header_Border, item, info, Header_Border);
//-------------------------------------------------------------------------------------------------------------------HANDY
#define ARRAY_SIZE(arry) (sizeof(arry)/sizeof(arry[0]))
#define PrintByte(byte) {for (int i = 7; 0 <= i; i--) {printf("%c", (byte & (1 << i)) ? '1' : '0');} printf("\n");}
//------------------------------------------------------------------------------------------------------------------------

#endif
