#ifndef CONFIGS_H_
#define CONFIGS_H_
/*-----------------------------------------------------------------------------------------------------MACROS CLIENT MODULE
Client Macros.
//-----------------------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
/*------------------------------------------------------------------------------------------------------------STATES CLIENT
BIT(N)                                    |    7    |    6    |    5    |    4    |    3    |    2    |    1    |    0    |
CONSTANT                                  |  ERROR  |    -    |    -    |    -    |  SRECV  |  SREQT  |  SCOMM  |  SCONN  |
-------------------------------------------------------------------------------------------------------------------------*/
#define SCONN 0   // State Connected.
#define SCOMM 1   // State Command.
#define SREQT 2   // State Request.
#define SRECV 3   // State Receive.

#define ERROR 7   /* Error.               Something went wrong-----------------------------------------------ERROR HANDLING
BIT(N)                                    |    15   |    14   |    13   |    12   |    11   |    10   |    9    |    8    |
ERROR HIGH BYTE                           |    -    |    -    |    -    |    -    |    -    |    -    |  MAERR  |  PIERR  |
---------------------------------------------------------------------------------------------------------------------------
BIT(N)                                    |    7    |    6    |    5    |    4    |    3    |    2    |    1    |    0    |
ERROR LOW BYTE                            |  PBERR  |  RSERR  |  SDERR  |  CPERR  |  IFERR  |  PDERR  |  PTERR  |  PSERR  |
-------------------------------------------------------------------------------------------------------------------------*/
#define PSERR 0   // Package Size         Package size is corrupted.
#define PTERR 1   // Package Terminate    Package isn't nullterminated.
#define PDERR 2   // Package Delimiter    Corrupted delimiter-format on package.
#define IFERR 3   // Iterate Fetch        Failed to fetch an item during iteration (wich should be in place).
#define CPERR 4   // Copy                 Copy (String) is corrupted.
#define SDERR 5   // Switch Default       Defaulted Switch-statement.
#define RSERR 6   // Request Send         Sent package is corrupted (control-size and send-size differ).
#define PBERR 7   // Protocol Byte        MSB (one or more bytes) in PROTOCOL isn't set.
#define PIERR 8   // Package Invalid      Package (response) has its VALID-flag cleared (Something went south server-side).
#define MAERR 9   // Memory Alloc         Failed to allocate memory.

/*-----------------------------------------------------------------------------------------------------------------PTOTOCOL
BIT (N)         INDEX (in PROTOCOL)            7         6         5         4         3          2         1        0
---------------------------------------------------------------------------------------------------------------------------
TABLE BYTE      0                         |  MSBIT  |    -    |    -    |    -    |    -    |    -    |  TDVCE  |  TMESG  |
---------------------------------------------------------------------------------------------------------------------------
ATTRIBUTE BYTE  1                         |  MSBIT  |  ATTR6  |  ATTR5  |  ATTR4  |  ATTR3  |  ATTR2  |  ATTR1  |  ATTR0  |
---------------------------------------------------------------------------------------------------------------------------
ECHO BYTE       2                         |  MSBIT  |  VALID  |    -    |    -    |    -    |     -   |    -    |  RWBIT  |
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
//---------------------------------------------------------------------------------------------------------------"GRAPHICS"
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
