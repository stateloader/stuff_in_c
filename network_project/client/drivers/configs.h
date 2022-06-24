/*----------------------------------------------------------------------------------------------------MACROS CLIENT MODULE
Macros implemented reg
------------------------------------------------------------------------------------------------------------------------*/
#ifndef CCONFIG_H_
#define CCONFIG_H_

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>

/*--------------------------------------------------------------------------------------------------------------TABLE BYTE
BIT(N)                              |    7    |    6    |    5    |    4    |    3    |     2    |     1     |     0     |
CONSTANT                            |  UNBIT  |    -    |    -    |    -    |    -    |     -    |   TDVCE   |   TMESG   |
--------------------------------------------------------------------------------------------------------------EXECUTE BYTE
BIT(N)                              |    7    |    6    |    5    |    4    |    3    |     2    |     1     |     0     |
CONSTANT                            |  UNBIT  |  RWBIT  |  EXEC5  |  EXEC4  |  EXEC3  |   EXEC2  |   EXEC1   |   EXEC0   |
--------------------------------------------------------------------------------------------------------------FORWARD BYTE
                                    |  UNBIT  |    -    |    -    |    -    |    -    |     -    |     -     |     -     |
------------------------------------------------------------------------------------------------------------------------*/         
#define TMESG 0     //              Table Message        - Set equals 'init message business' (to the server)
#define TDVCE 1     //              Table Device         - Set equals 'init device business' (to the server)

#define EXEC0 0     //              Execute #0             ---
#define EXEC1 1     //              Execute #1           
#define EXEC2 2     //              Execute #2             Execute Bit(N) (except RWBIT) with different local definitions 
#define EXEC3 3     //              Execute #3             depending on TABLE BYTE.
#define EXEC4 4     //              Execute #4             
#define EXEC5 5     //              Execute #5             ---
#define RWBIT 6     //              Read/Write          - Set equals database write, opposite equals read
//-------------------------------------------------------------------------------------------------------PROTOCOL INDEXING
#define TINDX 0     //              TABLE BYTE INDEX    - Its position in the protocol-array
#define EINDX 1     //              EXEC BYTE INDEX     - Its position in the protocol-array
#define FINDX 2     //              FWRD BYTE INDEX     - Its position in the protocol-array
#define POFFS 4     //              Protocol Offset     - size added to the request storing 3 protocol bytes and '\0'
//---------------------------------------------------------------------------------------------------------------DELIMITER
#define DELIM '|'   //              Delimiter           - Used as placeholder between a given model's entries.
#define DMSGE 5     //              Delimiters          - (members) Message-model
#define DDVCE 4     //              Delimiters          - (members) Device-model
//------------------------------------------------------------------------------------------------------------------------
#define FAIL 0      //              FAIL/FALSE          - Because I'm an idiot. Custom fun? <bool.h> exists, after all.  
#define SUCC 1      //              SUCC/TRUE           - Because I'm an idiot. Custom fun? <bool.h> exists, after all.  
//------------------------------------------------------------------------------------------------------------------BUFFER
#define FBUFF 4096  //              File Buffer
#define SBUFF 512   //              Scan Buffer
#define PBUFF 64    //              Path Buffer
#define TBUFF 21    //              DateTime Buffer
//--------------------------------------------------------------------------------------------------------------"GRAPHICS"
#define HEADER_FORM "%s\n%s\t\t%s\n%s\n\n"

#define Header_Bord "----------------------------------------------------------------------------------------------------"
#define Render_Header(itm, inf) printf(HEADER_FORM, Header_Bord, itm, inf, Header_Bord);

#define SYSTEM_FORM "\t\t\tSystem: %s\n"
#define System_Message(sysmesg) printf(SYSTEM_FORM, sysmesg);
//-------------------------------------------------------------------------------------------------------------SOME CHECKS
#define check_delm(str, len) (str[len - 1] == DELIM)
#define check_size(scn, buf) (scn < buf - 1) 
#define check_term(scn, len) (scn[len - 1] == '\0')
//-------------------------------------------------------------------------------------------------------------------OTHER
#define PrintByte(msk) {for (int i = 7; 0 <= i; i--) {printf("%c", (msk & (1 << i)) ? '1' : '0');} printf("\n");}
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))
#define Print_Numb(num, not) printf("TEST---NUMBER: %d ---NOTE %s\n", num, not);

#endif