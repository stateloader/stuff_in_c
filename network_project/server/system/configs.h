/*-----------------------------------------------------------------------------------------------------MACROS SERVER MODULE
Macros implemented reg                                                                                                   
//-----------------------------------------------------------------------------------------------------------------------*/
#ifndef CONFIGS_H_
#define CONFIGS_H_

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>

#define UNBIT 7

/*-------------------------------------------------------------------------------------------------------------------------
BIT(N)                                    |    15   |    14   |    13   |    12   |    11   |    10   |    9    |    8    |
ERROR HIGH BYTE                           |  RCERR  |  DDERR  |  FRERR  |  FWERR  |  PCERR  |  RUERR  |  RTERR  |  RSERR  |
---------------------------------------------------------------------------------------------------------------------------
BIT(N)                                    |    7    |    6    |    5    |    4    |    3    |    2    |    1    |    0    |
ERROR HIGH BYTE                           |  RWERR  |  FOERR  |  ITERR  |  SWERR  |  CAERR  |  CLERR  |  SCERR  |  SSERR  |
-------------------------------------------------------------------------------------------------------------------------*/

#define SSERR 0                             // Server socket Error.
#define SCERR 1                             // Server connection Error.
#define CLERR 2                             // Server listening (On Client) Error.
#define CAERR 3                             // Failed to accepting client.
#define SWERR 4                             // Switch statement has reached Default.
#define ITERR 5                             // Iteration failed (where a match should has been vailable).
#define FOERR 6                             // Failed to Open file.
#define RWERR 7                             // Failed to read/write to file.
#define RSERR 8                             // Received package is below lowest accepted size.
#define RTERR 9                             // Received package isn't nullterminated.
#define RUERR 10                            // Received package has a corrupted protocol.
#define PCERR 11                            // Package copy failure.
#define FWERR 12                            // Failed to write (append) to file.
#define FRERR 13                            // Failet do read from file.
#define DDERR 14                            // Delimiter error.
#define RCERR 15                            // Failed to response client.

//--------------------------------------------------------------------------------------------------------SERVER CONTROLLER

/*-------------------------------------------------------------------------------------------------------------------------
BIT(N)                                    |    15   |    14   |    13   |    12   |    11   |    10   |    9    |    8    |
ERROR HIGH BYTE                           |    -    |    -    |    -    |    -    |    -    |    -    |    -    |    -    |
---------------------------------------------------------------------------------------------------------------------------
BIT(N)                                    |    7    |    6    |    5    |    4    |    3    |    2    |    1    |    0    |
CONSTANT                                  |  ERROR  |    -    |    -    |  RECVF  |  SCACC  |  SSONN  |  SSOCK  |  ALIVE  |
-------------------------------------------------------------------------------------------------------------------------*/

#define ALIVE 0                           // When set, a session is ongoing and nothing has went south. Yet.
#define SSOCK 1                           // When set, the server has sucessfully created a socket
#define SSONN 2                           // When set, the server has successfully binded socket to address.
#define SCACC 3                           // When set, the client has been acepted by the server.
#define RECVF 4                           // When set, a response has successfully been revieved from the server.
#define ERROR 7                           // Something went wrong. Always results in terminate.

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