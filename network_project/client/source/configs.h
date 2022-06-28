/*----------------------------------------------------------------------------------------------------MACROS CLIENT MODULE
Macros implemented reg
------------------------------------------------------------------------------------------------------------------------*/
#ifndef CONFIG_H_
#define CONFIG_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
#define RWBIT 6     //              Read/Write          - Set equals database write, opposite equals database read
//-------------------------------------------------------------------------------------------------------PROTOCOL INDEXING
#define TINDX 0     //              TABLE BYTE INDEX    - Its position in the protocol-array
#define EINDX 1     //              EXEC BYTE INDEX     - Its position in the protocol-array
#define FINDX 2     //              FWRD BYTE INDEX     - Its position in the protocol-array
#define POFFS 4     //              Protocol Offset     - size added to the package storing the protocol-bytes and '\0'
//---------------------------------------------------------------------------------------------------------------DELIMITER
#define DELIM '|'   //              Delimiter           - Used as placeholder between a given model's entries.
#define DMSGE 4     //              Delimiters          - (members) Message-model
#define DDVCE 4     //              Delimiters          - (members) Device-model
//------------------------------------------------------------------------------------------------------------------------
#define FLEE -2     //              FLEE/PANIC          - Something went south enough to force quit the entire program.
#define EXIT -1     //              EXIT                - User wants to exit the program.
#define FAIL 0      //              FAIL/FALSE          - Because I'm an idiot. Custom fun? <bool.h> exists, after all.
#define SUCC 1      //              SUCC/TRUE           - Because I'm an idiot. Custom fun? <bool.h> exists, after all.
//------------------------------------------------------------------------------------------------------------------BUFFER
#define FBUFF 4096  //              File Buffer
#define SBUFF 512   //              Scan Buffer
#define PBUFF 64    //              Path Buffer
#define TBUFF 21    //              DateTime Buffer
//--------------------------------------------------------------------------------------------------------------"GRAPHICS"
#define HEADER_FORM "\n%s\t\t%s\n%s\n\n"
#define Header_Border "----------------------------------------------------------------------------------------------------"
#define Render_Header(itm, inf) printf(HEADER_FORM, itm, inf, Header_Border);

#define FORM_INFO "\t\t\tSystem: %s\n"
#define Message_Info(inf) printf(FORM_INFO, inf);

#define FORM_FLEE "\t\t\tFatal: %s\n\t\t\t%s\n\t\t\t%s\n"
#define Message_Flee(inf, exp, tip) printf(FORM_FLEE, inf, exp, tip)
//-------------------------------------------------------------------------------------------------------------SOME CHECKS
#define check_delm(str, len) (str[len - 1] == DELIM)
#define check_size(str, buf) (str < buf - 1)
#define check_term(str, len) (str[len - 1] == '\0')
//-------------------------------------------------------------------------------------------------------------------OTHER
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))
#define PrintByte(msk) {for (int i = 7; 0 <= i; i--) {printf("%c", (msk & (1 << i)) ? '1' : '0');} printf("\n");}
//--------------------------------------------------------------------------------------------------------------THROUGHOUTS
int8_t datetime_append(char *datetime);
int8_t protocol_append(char *package, int32_t size_pack, uint8_t *protocol);

#endif

//#define Print_Numb(num, not) printf("TEST---NUMBER: %d ---NOTE %s\n", num, not);
//