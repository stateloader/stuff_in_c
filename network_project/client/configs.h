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
CONSTANT                                  |  ERROR  |    -    |    -    |  RECVF  |  REQTF  |  CMNDF  |  CONNF  |  ALIVE  |
-------------------------------------------------------------------------------------------------------------------------*/
#define ALIVE 0                           // When set, a session is ongoing and nothing has went south. Yet.
#define CONNF 1                           // When set, the client has successfully connected to the server.
#define CMNDF 2                           // When set, the client has successfully made a request.
#define REQTF 3                           // When set, the request has successfully been sent to the server.
#define RECVF 4                           // When set, a response has successfully been revieved from the server.
#define ERROR 7                           // Something went wrong. Always results in terminate.

//-----------------------------------------------------------------------------------------------------------ERROR HANDLING

/*-------------------------------------------------------------------------------------------------------------------------
BIT(N)                                    |    15   |    14   |    13   |    12   |    11   |    10   |    9    |    8    |
ERROR HIGH BYTE                           |  SDERR  |    -    |  MMERR  |  IVERR  |  DCERR  |  PBERR  |  RRERR  |  RSERR  |
---------------------------------------------------------------------------------------------------------------------------
BIT(N)                                    |    7    |    6    |    5    |    4    |    3    |    2    |    1    |    0    |
ERROR LOW BYTE                            |  SDERR  |  TPERR  |  IIERR  |  PDERR  |  PTERR  |  PSERR  |  COERR  |  SOERR  |
-------------------------------------------------------------------------------------------------------------------------*/
#define SOERR 0                           // Socket error, we didn't even manage to create a socket.                          
#define COERR 1                           // Connect error, couldn't connect to the server.
#define PSERR 2                           // Package size error, sizes between sent and created doesn't match. 
#define PTERR 3                           // Package (not) terminated error, package isn't nullterminated.
#define PDERR 4                           // The supposed amount the entry's delimiter-constant supposed to be is wrong.
#define IIERR 5                           // Failed to fetch an item (wich should be in place).
#define TPERR 6                           // <until filling for now>
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
//-------------------------------------------------------------------------------------------------------------------HANDY
#define ARRAY_SIZE(arry) (sizeof(arry)/sizeof(arry[0]))
//--------------------------------------------------------------------------------------------------------------"GRAPHICS"
#define HEADER_FORM "\n%s\n%s\t\t%s\n%s\n\n"
#define Header_Border "--------------------------------------------------------------------------------------------------"
#define Render_Header(itm, inf) printf(HEADER_FORM, Header_Border, itm, inf, Header_Border);
//-------------------------------------------------------------------------------------------------------------------DEBUG
#define PrintByte(byte) {for (int i = 7; 0 <= i; i--) {printf("%c", (byte & (1 << i)) ? '1' : '0');} printf("\n");}

inline static void print_string_and_size(char *string, size_t size_strg) {
  printf("\tstring           --  %s\n", string);
  printf("\tsize_string      --  %ld\n", size_strg);
}
inline static void print_TBIDX(uint8_t tbidx) {
  printf("\tcurrent TBIDX    -- ");
  PrintByte(tbidx);
}
inline static void print_ABIDX(uint8_t abidx) {
  printf("\tcurrent TBIDX    -- ");
  PrintByte(abidx);
}
inline static void print_EBIDX(uint8_t ebidx) {
  printf("\tcurrent TBIDX    -- ");
  PrintByte(ebidx);
}
inline static void print_username(char *username, size_t size_user) {
  printf("\tcurrent username  -- %s\n", username);
  printf("\tcurrent size_pack -- %ld\n", size_user);

}
inline static void print_password(char *password, size_t size_pass) {
  printf("\tcurrent password  -- %s\n", password);
  printf("\tcurrent size_pass -- %ld\n", size_pass);

}
inline static void print_package(char *package, size_t size_pack) {
  printf("\tcurrent package   -- %s\n", package);
  printf("\tcurrent size_pack -- %ld\n", size_pack);
}
//------------------------------------------------------------------------------------------------------------------------


#endif
