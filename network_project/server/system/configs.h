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
ERROR HIGH BYTE                           |  RCERR  |  DDERR  |  FRERR  |  FWERR  |  PCERR  |  RUERR  |  RTERR  |  RSERR  |
---------------------------------------------------------------------------------------------------------------------------
BIT(N)                                    |    7    |    6    |    5    |    4    |    3    |    2    |    1    |    0    |
ERROR HIGH BYTE                           |  RWERR  |  FOERR  |  ITERR  |  SWERR  |  CAERR  |  CLERR  |  SCERR  |  SSERR  |
-------------------------------------------------------------------------------------------------------------------------*/
/*
#define PSERR 0   // Package Size         Package size is corrupted.
#define PTERR 1   // Package Terminate    Package isn't nullterminated.
#define PDERR 2   // Package Delimiter    Corrupted delimiter-format on package.
#define IFERR 3   // Iterate Fetch        Failed to fetch an item during iteration (wich should be in place).
#define CPERR 4   // Copy                 Copy (String) is corrupted.
#define SDERR 5   // Switch Default       Defaulted Switch-statement.
#define RSERR 6   // Response Send        Sent package is corrupted (control-size and send-size differ).
#define PBERR 7   // Protocol Byte        MSB (one or more bytes) in PROTOCOL isn't set.
#define PIERR 8   // Package Invalid      Package (response) has its VALID-flag cleared (Something went south server-side).
#define MAERR 9   // Memory Alloc         Failed to allocate memory.
*/

#define SSERR 0                           // Server socket Error.
#define SCERR 1                           // Server connection Error.
#define CLERR 2                           // Server listening (On Client) Error.
#define CAERR 3                           // Failed to accepting client.
#define SWERR 4                           // Defaulted Switch-statement.
#define ITERR 5                           // Iteration failed (where a match should has been vailable).
#define FOERR 6                           // Failed to Open file.
#define RWERR 7                           // Failed to read/write to file.
#define RSERR 8                           // Received package is below lowest accepted size.
#define RTERR 9                           // Received package isn't nullterminated.
#define RUERR 10                          // Received package has a corrupted protocol.
#define PCERR 11                          // Package copy failure.
#define FWERR 12                          // Failed to write to file.
#define FRERR 13                          // Failet do read from file.
#define DDERR 14                          // Delimiter error.
#define RCERR 15                          // Failed to response client.

/*-----------------------------------------------------------------------------------------------------------------PTOTOCOL
BIT (N)          INDEX (in PROTOCOL)            7         6         5         4         3          2         1        0
---------------------------------------------------------------------------------------------------------------------------
TABLE BYTE         0                       |  MSBIT  |    -    |    -    |    -    |    -    |    -    |  TDVCE  |  TMESG |
---------------------------------------------------------------------------------------------------------------------------
ATTRIBUTE BYTE     1                       |  MSBIT  |  ATTR6  |  ATTR5  |  ATTR4  |  ATTR3  |  ATTR2  |  ATTR1  |  ATTR0 |
---------------------------------------------------------------------------------------------------------------------------
ECHO BYTE          3                       |  MSBIT  |  VALID  |    -    |    -    |    -    |     -   |    -    |  RWBIT |
-------------------------------------------------------------------------------------------------------------------------*/
#define MSBIT 7
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