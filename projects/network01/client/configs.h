#ifndef CONFIGS__H_
#define CONFIGS__H_
/*------------------------------------------------------------------------------------MACROS CLIENT
Now, this is what it is - an experimental play with bitwise operations - and nothing that made my
code more readable nor more "clever".

The 'STATE CLIENT'-byte lets the system know where in the application-part of the process we are.
As for now I don't use this bit-configuration for utilize for anything useful.
-------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
/*------------------------------------------------------------------------------------States Client
BIT(N)            |    7    |    6    |    5    |    4    |    3    |    2    |    1    |    0    |
CONSTANT          |    -    |    -    |    -    |    -    |  SRECV  |  SREQT  |  SCOMM  |  SCONN  |
-------------------------------------------------------------------------------------------------*/

#define SCONN 0   // State Connected.
#define SCOMM 1   // State Command.
#define SREQT 2   // State Request.
#define SRECV 3   // State Receive.

/*-----------------------------------------------------------------------------------------PROTOCOL
BIT (N)                7         6         5         4         3          2         1        0
---------------------------------------------------------------------------------------------------
TABLE BYTE        |  MSBIT  |    -    |    -    |    -    |    -    |    -    |  TDVCE  |  TMESG  |
---------------------------------------------------------------------------------------------------
PERFORM BYTE			|  MSBIT  |  PERF6  |  PERF5  |  PERF4  |  PERF3  |  PERF2  |  PERF1  |  PERF0  |
---------------------------------------------------------------------------------------------------
CHECK BYTE				|  MSBIT  |   -     |    -    |    -    |    -    |  CFAIL  |  SFAIL  |  PPREQ  |
-------------------------------------------------------------------------------------------------*/

#define TINDX 0   // Table Byte Index.   Flags tables (message, device, <tables to come>).

#define PINDX 1   /* Perform Byte Index. Flags a specific action to perform regarding tables.
									                       Right now just leds being switched on a device but guess
									                       CRUDE-functionality lives here down the road.*/
									                       	
#define CINDX 2   /* Check Byte Index.   Flags pull/push-request to server. If the server detects
																				 any errors in received package, bits will be set (in time)
																				 explaining the problem and included in the response.*/
//---------------------------------------------------------------------------------------Table Bits
#define TMESG 0   // Table Message Bit
#define TDVCE 1   // Table Device Bit
 //------------------------------------------------------------------------------------Perform Bits
#define PERF0 0
#define PERF1 1
#define PERF2 2
#define PERF3 3
#define PERF4 4
#define PERF5 5
#define PERF6 6
//---------------------------------------------------------------------------------------Check Bits
#define PPREQ 0   // Push (or) Pull Request.
#define CFAIL 1		// Client Fail. (something wrong with received package).
#define SFAIL 2		// Server Fail. (server having a bad day).
#define MSBIT 7   // Most Significant Bit. Always set in bytes belonging to PROTOCOL.
//------------------------------------------------------------------------------------------Buffers
#define RBUFF 4096// Receive Buffer.		Max bytes possible to receive (i.e: tabk)
#define SBUFF 512 // Standard Buffer.
#define TBUFF 22  // Time Buffer.
#define POFFS 4   // Package offset.    Size added/reduced for 'protocol' (and terminator).
//----------------------------------------------------------------------------------------Delimiter
#define DELIM '|' // Delimiter.
#define DMESG 4   // Delemiters Message.
#define DDVCE 3   // Delimiters Device.
//------------------------------------------------------------------------------------------"Stuff"
#define System_Message(info) printf("\t\t\t%s\n", info);

static inline void Termination_Message(const char *func, const char *cause) {
/*failures/errors detected going to terminate the show*/
	fprintf(stderr, "\nERROR | File [%s] Func [\"%s\"] Time [%s]" \
		"\nCAUSE | %s\nProgram will Terminate...\n",
		__FILE__, func, __DATE__, cause
	);
	exit(EXIT_FAILURE);
}

#define HEADER_FORM "\n%s\n%s\t\t\t%s\n%s\n\n"
#define Header_Border "--------------------------------------------------------------------------------------------------"
#define Render_Header(item, info) printf(HEADER_FORM, Header_Border, item, info, Header_Border);
//-------------------------------------------------------------------------------------------------------------------HANDY
#define ARRAY_SIZE(arry) (sizeof(arry)/sizeof(arry[0]))
#define PrintByte(byte) {for (int i = 7; 0 <= i; i--) {printf("%c", (byte & (1 << i)) ? '1' : '0');} printf("\n");}
//------------------------------------------------------------------------------------------------------------------------

#endif
