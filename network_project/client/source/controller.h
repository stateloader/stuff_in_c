/*----------------------------------------------------------------------------------------------------MACROS CLIENT MODULE
Macros implemented reg
------------------------------------------------------------------------------------------------------------------------*/
#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>

/*---------------------------------------------------------------------------------------------------------------TABLE BYTE
BIT(N)                              |    7    |    6    |    5    |    4    |    3    |     2    |     1     |     0     |
CONSTANT                            |  UNBIT  |    -    |    -    |    -    |    -    |     -    |   TDVCE   |   TMESG   |
------------------------------------------------------------------------------------------------------------ATTRIBUTE BYTE
BIT(N)                              |    7    |    6    |    5    |    4    |    3    |     2    |     1     |     0     |
CONSTANT                            |  UNBIT  |  RWBIT  |  ATTR5  |  ATTR4  |  ATTR3  |   ATTR2  |   ATTR1   |   ATTR0   |
-------------------------------------------------------------------------------------------------------------- STATUS BYTE
                                    |  UNBIT  |  VALID  |  SETUP  |  LOGIN  |    -    |     -    |     -     |   LINKA   |
------------------------------------------------------------------------------------------------------------------------*/
#define UNBIT 7

/*-------------------------------------------------------------------------------------------------------PROTOCOL INDEXING
TABLE BYTE, ATTRIBUTE BYTE and STATUS BYTE are throughout the program indexed in an uint8_t array - 'protocol'. Given byte
in the index are reffered to as below:
------------------------------------------------------------------------------------------------------------------------*/
#define TBYTE 0     //              TABLE BYTE          - index 0 in protocol-array
#define ABYTE 1     //              ATTRIBUTE BYTE      - index 1 in protocol-array
#define SBYTE 2     //              STATUS BYTE         - index 2 in protocol-array

//--------------------------------------------------------------------------------------------------------TABLE BYTE flags
#define TMESG 0     //              Table Message       - Set equals 'init message business' (to the server)
#define TDVCE 1     //              Table Device        - Set equals 'init device business' (to the server)

//----------------------------------------------------------------------------------------------------ATTRIBUTE BYTE flags
#define ATTR0 0     //              Attribute #0        ----
#define ATTR1 1     //              Attribute #0        
#define ATTR2 2     //              Attribute #0         Attribute Bit(N) (except RWBIT) with different local definitions
#define ATTR3 3     //              Attribute #0         depending on TABLE BYTE.
#define ATTR4 4     //              Attribute #0        
#define ATTR5 5     //              Attribute #0        ----
#define RWBIT 6     //              Read/Write          - Set equals database write, opposite equals database read

//-------------------------------------------------------------------------------------------------------STATUS BYTE flags
#define LINKA 0
#define LOGIN 4
#define SETUP 5
#define VALID 6
/*----------------------------------------------------------------------------------------------------------------DELIMITER
ingo info
//-----------------------------------------------------------------------------------------------------------------------*/
#define DELIM '|'   //              Delimiter           - Used as placeholder between a given model's entries.
#define DMSGE 4     //              Delimiters          - (members) Message-model
#define DDVCE 3     //              Delimiters          - (members) Device-model
#define DACCS 2
#define POFFS 4     //              Protocol Offset     - size added to end of package, storing the protocol-bytes and '\0'
//------------------------------------------------------------------------------------------------------------------------
#define FLEE -2     //              FLEE/PANIC          - Something went south enough to force quit the entire program.
#define EXIT -1     //              EXIT                - User wants to exit the program.
#define FAIL 0      //              FAIL/FALSE          - Because I'm an idiot. Custom fun? <bool.h> exists, after all.
#define SUCC 1      //              SUCC/TRUE           - Because I'm an idiot. Custom fun? <bool.h> exists, after all.
//------------------------------------------------------------------------------------------------------------------BUFFER
#define FBUFF 4096 //              File Buffer
#define SBUFF 512   //              Scan Buffer
#define PBUFF 64    //              Path Buffer
#define TBUFF 21    //              DateTime Buffer
//--------------------------------------------------------------------------------------------------------------"GRAPHICS"
#define HEADER_FORM "\n%s\n%s\t\t%s\n%s\n\n"
#define Header_Border "----------------------------------------------------------------------------------------------------"
#define Render_Header(itm, inf) printf(HEADER_FORM, Header_Border, itm, inf, Header_Border);

#define FORM_INFO "\t\t\t%s\n"
#define System_Message(inf) printf(FORM_INFO, inf);

#define FORM_FLEE "\t\t\tFatal: %s\n\t\t\t%s\n"
#define Message_Flee(inf, exp) printf(FORM_FLEE, inf, exp)
//-------------------------------------------------------------------------------------------------------------SOME CHECKS
#define check_delm(str, len) (str[len - 1] == DELIM)
#define check_size(str, buf) (str < buf - 1)
#define check_term(str, len) (str[len - 1] == '\0')
//-------------------------------------------------------------------------------------------------------------------OTHER
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))
#define PrintByte(msk) {for (int i = 7; 0 <= i; i--) {printf("%c", (msk & (1 << i)) ? '1' : '0');} printf("\n");}
//--------------------------------------------------------------------------------------------------------------CONTROLLERS

#endif
