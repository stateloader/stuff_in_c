/*-----------------------------------------------------------------------------------------------------MACROS CLIENT MODULE
Macros implemented reg                                                                                                   
//-----------------------------------------------------------------------------------------------------------------------*/
#ifndef CONFIGS_H_
#define CONFIGS_H_

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

//---------------------------------------------------------------------------------------------------------------CONTROLLER


/*--------------------------------------------------------------------------------------------------------------------State
BIT(N)                                    |    7    |    6    |    5    |    4    |    3    |    2    |    1    |    0    |
CONSTANT                                  |  ERROR  |    -    |    -    |    -    |  SRECV  |  SREQT  |  SCOMM  |  SCONN  |
-------------------------------------------------------------------------------------------------------------------------*/
#define SCONN 0                           // State Connected When set, the client has successfully connected to server.
#define SCOMM 1                           // State Command. When set, the client has successfully choosed a command.
#define SREQT 2                           // State Request. When set, the client has successfully sent a request.
#define SRECV 3                           // State Receive. When set, the cient has successfully recieved a response.

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
The protocol, throughout the comments referred to as 'PROTOCOL' consist of 4 bytes. 3 unsigned and a signed terminator.
This protocol will be attached at the end of every package from both the server and the client during transmissions. For
the moment it's just possble to write/read records regarding comments and interact with the device and read its historical
records. Much logic across the program is mostly in place for (eventual) later implementations. 

BIT (N)          INDEX (IN PROTOCOL)           7         6         5         4         3          2         1        0
---------------------------------------------------------------------------------------------------------------------------
TABLE BYTE              0                  |  UNBIT  |    -    |    -    |    -    |    -    |    -    |  TDVCE  |  TMESG |
---------------------------------------------------------------------------------------------------------------------------
ATTRIBUTE BYTE          1                  |  UNBIT  |  ATTR6  |  ATTR5  |  ATTR4  |  ATTR3  |  ATTR2  |  ATTR1  |  ATTR0 |
---------------------------------------------------------------------------------------------------------------------------
ECHO BYTE               3                  |  UNBIT  |  VALID  |    -    |    -    |    -    |     -   |    -    |  RWBIT |
---------------------------------------------------------------------------------------------------------------------------
TERMINATOR              4                  |                                     NULL                                     |
-------------------------------------------------------------------------------------------------------------------------*/
#define UNBIT 7
//---------------------------------------------------------------------------------------------------------------TABLE BITS
#define TMESG 0                           // Table Message Byte, indicates there's message-business ongoing.
#define TDVCE 1                           // Table Device Byte, indicates there's device-business ongoing.
//-----------------------------------------------------------------------------------------------------------ATTRIBUTE BITS
#define ATTR0 0
#define ATTR1 1
#define ATTR2 2
#define ATTR3 3
#define ATTR4 4
#define ATTR5 5
#define ATTR6 6
//---------------------------------------------------------------------------------------------------------------ECHO BITS
#define RWBIT 0                           // Read/Write bit.
#define VALID 6
//------------------------------------------------------------------------------------------------------------------------
#define TBIDX 0                           // Table Byte Index (in PROTOCOL).
#define ABIDX 1                           // Attribute Byte Index (in PROTOCOL).
#define EBIDX 2                           // EXHO Byte Index (in PROTOCOL).
//-----------------------------------------------------------------------------------------------------------------BUFFERS
#define RBUFF 4096                        // Receive Buffer
#define SBUFF 512                         // Standard (Input) Buffer.
#define TBUFF 22                          // Datetime Buffer
#define POFFS 4                           // Package offset (size added for 3 protocol bytes and a terminator.
//---------------------------------------------------------------------------------------------------------------DELIMITER
#define DELIM '|'                         // 
#define DMESG 4
#define DDVCE 3
//----------------------------------------------------------------------------------------------------------------GRAPHICS
#define FORM_INFO "\t\t\t%s\n"
#define System_Message(info) printf(FORM_INFO, info);

#define HEADER_FORM "\n%s\n%s\t\t\t%s\n%s\n\n"
#define Header_Border "--------------------------------------------------------------------------------------------------"
#define Render_Header(itm, inf) printf(HEADER_FORM, Header_Border, itm, inf, Header_Border);
//-------------------------------------------------------------------------------------------------------------------HANDY
#define ARRAY_SIZE(arry) (sizeof(arry)/sizeof(arry[0]))
#define PrintByte(byte) {for (int i = 7; 0 <= i; i--) {printf("%c", (byte & (1 << i)) ? '1' : '0');} printf("\n");}
//------------------------------------------------------------------------------------------------------------------------

#endif
