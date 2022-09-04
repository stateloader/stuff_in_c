#ifndef CONFIGS__H_
#define CONFIGS__H_
/*------------------------------------------------------------------------------------MACROS SERVER
Now, this is what it is - an experimental play with bitwise operations - and nothing that made my
code more readable nor more "clever".

In a nutshell, the 'STATE CLIENT'-byte lets the system know where in the application-part of the
process we are. As for now, the process doesn't use this bit-configuration for anything useful.

These error-bits are set throughout the source-files when errors accurs and "summarized" after
given sessions 4-step process is done (connect, command, request, receive). 
-------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
/*------------------------------------------------------------------------------------States Client
BIT(N)            |    7    |    6    |    5    |    4    |    3    |    2    |    1    |    0    |
CONSTANT          |    -    |    -    |    -    |    -    |    -    |  SRESP  |  SRECV  |  SCONN  |
-------------------------------------------------------------------------------------------------*/

#define SCONN 0   // State Connected.
#define SREQT 2   // State Request.
#define SRECV 3   // State Receive.

/*-----------------------------------------------------------------------------------Protocol-flags
BIT (N)                7         6         5         4         3          2         1        0
---------------------------------------------------------------------------------------------------
TABLE BYTE        |  MSBIT  |    -    |    -    |    -    |    -    |    -    |  TDVCE  |  TMESG  |
---------------------------------------------------------------------------------------------------
PERFORM BYTE			|  MSBIT  |  PERF6  |  PERF5  |  PERF4  |  PERF3  |  PERF2  |  PERF1  |  PERF0  |
---------------------------------------------------------------------------------------------------
CHECK BYTE				|  MSBIT  |   -     |    -    |    -    |    -    |     -   |    -    |  PPREQ  |
-------------------------------------------------------------------------------------------------*/

#define TINDX 0   // Table Byte Index.   Flags request-table (message, device, <tables to come>).
#define PINDX 1   // Perform Byte Index. Flags what to do with the table (read, write, <to come>).
#define CINDX 2   // Check Byte Index.   Flags of 
//---------------------------------------------------------------------------------------Table Bits
#define TMESG 0   // Table Message Bit
#define TDVCE 1   // Table Device Bit
//-------------------------------------------------------------------------------------Perform Bits
#define PERF0 0
#define PERF1 1
#define PERF2 2
#define PERF3 3
#define PERF4 4
#define PERF5 5
#define PERF6 6
//---------------------------------------------------------------------------------------Check Bits
#define PPREQ 0   // Push (or) Pull Request
#define MSBIT 7   // Most Significant Bit. Always set in bytes belonging to PROTOCOL.
//------------------------------------------------------------------------------------------Buffers
#define RBUFF 4096// Receive Buffer.		Max bytes possible to receive.
#define SBUFF 512 // Send Buffer.				Max bytes possible to send.
#define TBUFF 22  // Time Buffer.
#define POFFS 4   // Package offset.    Size added/reduced for 'protocol' (and a terminator).
/*----------------------------------------------------------------------------------------DELIMITER

-------------------------------------------------------------------------------------------------*/
#define DELIM '|' // Delimiter.
#define DMESG 4   // Delemiters Message.
#define DDVCE 3   // Delimiters Device.

#define System_Message(info) printf("\t\t\t%s\n", info);

static inline void Termination_Message(const char *func, const char *cause) {
/*failures/errors detected going to terminate the show*/
	fprintf(stderr, "\nERROR | File [%s] Func [\"%s\"] Time [%s]" \
		"\nCAUSE | %s\nProgram will Terminate...\n",
		__FILE__, func, __DATE__, cause
	);
	exit(EXIT_FAILURE);
}

static inline void Warning_Message(const char *func, const char *cause) {
/*failures/errors detected going to terminate the show*/
	fprintf(stderr, "\nWARNING | File [%s] Func [\"%s\"] Time [%s]" \
		"\nCAUSE | %s\nProgram will Terminate...\n",
		__FILE__, func, __DATE__, cause
	);
}

#define HEADER_FORM "\n%s\n%s\t\t\t%s\n%s\n\n"
#define Header_Border "--------------------------------------------------------------------------------------------------"
#define Render_Header(item, info) printf(HEADER_FORM, Header_Border, item, info, Header_Border);
//-------------------------------------------------------------------------------------------------------------------HANDY
#define ARRAY_SIZE(arry) (sizeof(arry)/sizeof(arry[0]))
#define PrintByte(byte) {for (int i = 7; 0 <= i; i--) {printf("%c", (byte & (1 << i)) ? '1' : '0');} printf("\n");}
//------------------------------------------------------------------------------------------------------------------------

#endif
