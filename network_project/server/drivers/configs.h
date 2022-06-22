#ifndef CONFIGS_H_
#define CONFIGS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>

/*---------------------------------------------------------------------------------------------------------------TASK BYTE
Bit                                 |    7    |    6    |    5    |    4    |    3    |     2    |     1     |     0     |
Constant                            |  UNBIT  |    -    |    -    |    -    |    -    |     -    |   TDVCE   |   TMESG   |
--------------------------------------------------------------------------------------------------------------EXECUTE BYTE
Bit                                 |    7    |    6    |    5    |    4    |    3    |     2    |     1     |     0     |
Constant                            |  UNBIT  |  RWBIT  |  EXEC5  |  EXEC4  |  EXEC3  |   EXEC2  |   EXEC1   |   EXEC0   |
--------------------------------------------------------------------------------------------------------------FORWARD BYTE
-                                                       A just-in-case-byte for/if later "inventions".
-                                   |  UNBIT  |    -    |    -    |    -    |    -    |     -    |     -     |     -     |
------------------------------------------------------------------------------------------------------------------------*/           
#define TMESG 0     //              Task Message        - Set means init message business
#define TDVCE 1     //              Task Device         - Set means init device business

#define EXEC0 0     //              Execute #0
#define EXEC1 1     //              Execute #1           
#define EXEC2 2     //              Execute #2           Execute Bit(N) (except RWBIT) with different local definitions 
#define EXEC3 3     //              Execute #3           depending on TASK.   
#define EXEC4 4     //              Execute #4
#define EXEC5 5     //              Execute #5
#define RWBIT 6     //              Read/Write          - Set means database write, opposite read.
//-------------------------------------------------------------------------------------------------------PROTOCOL INDEXING
#define TINDX 0     //              Task Byte Index     - Its position in the protocol-array.
#define EINDX 1     //              Execution Byte Index- Its position in the protocol-array.
#define FINDX 2     //              Forward Byte Index  - Its position in the protocol-array.
#define POFFS 4     //              Protocol Offset     - size added to the request storing 3 protocol bytes and '\0'
//------------------------------------------------------------------------------------------------------------------------
#define DDVCE 4     //              Delimitera (members) Device-model
#define DMSGE 4     //              Delimiters (members) Message-model
//------------------------------------------------------------------------------------------------------------------------
#define DELIM '|'   //              Delimiter used as placeholder between a given model's entries.
#define FAIL 0
#define SUCC 1
//------------------------------------------------------------------------------------------------------------------------
#define FBUFF 4096      //          File Buffer
#define SBUFF 512       //          Scan Buffer
#define PBUFF 64        //          Path Buffer
#define TBUFF 24        //          Time (DateTime) Buffer
//--------------------------------------------------------------------------------------------------------------"Graphics"
#define HEADER_FORM "%s\n%s\t\t%s\n%s\n\n"

#define Header_Bord "----------------------------------------------------------------------------------------------------"
#define Render_Header(itm, inf) printf(HEADER_FORM, Header_Bord, itm, inf, Header_Bord);

#define SYSTEM_FORM "  %s\n"
#define System_Message(sysmesg) printf(SYSTEM_FORM, sysmesg);
//-------------------------------------------------------------------------------------------------------------some checks
#define check_delm(str, len) (str[len - 1] == DELIM)
#define check_size(scn, buf) (scn < buf - 1) 
#define check_term(scn, len) (scn[len - 1] == '\0')
#define check_tedl(str, len) (str[len - 3] == '|')
#define check_cnum(nm0, nm1) (nm0 == nm1)
#define check_endf(str, len) (str[len - 2] == '|' && str[len - 1] == '\0')
//--------------------------------------------------------------------------------------------------------------------bits
#define fetch_endb(byt, str, len) (byt = str[len - 2])
#define parse_rewr(msk) (msk & (1 << 7))
//-------------------------------------------------------------------------------------------------------------------other
#define PrintByte(msk) {for (int i = 7; 0 <= i; i--) {printf("%c", (msk & (1 << i)) ? '1' : '0');} printf("\n");}
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))
#define Print_Numb(num, not) printf("TEST---NUMBER: %d ---NOTE %s\n", num, not);

#endif