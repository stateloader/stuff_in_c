#ifndef CONFIGS__H_
#define CONFIGS__H_
/*------------------------------------------------------------------------------------MACROS SERVER
More or less a copy of the client-config. However, unlike client the server is made to not
terminate for every single error why it has a 'status'-byte (STATUS SERVER) that works a little bit
different from its client-buddy.
-------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
/*------------------------------------------------------------------------------------STATUS SERVER
BIT(N)            |    7    |    6    |    5    |    4    |    3    |    2    |    1    |    0    |
CONSTANT          |    -    |    -    |    -    |    -    |    -    |  STERM  |  CWARN  |  SCONN  |
-------------------------------------------------------------------------------------------------*/
#define SCONN 0   // Server Connected.
#define CWARN 1		// Client Warning.
#define STERM 2   // Server (Force) Termination.
/*-----------------------------------------------------------------------------------------PROTOCOL
BIT (N)                7         6         5         4         3          2         1        0
---------------------------------------------------------------------------------------------------
TABLE BYTE        |  MSBIT  |    -    |    -    |    -    |    -    |    -    |  TDVCE  |  TMESG  |
---------------------------------------------------------------------------------------------------
PERFORM BYTE			|  MSBIT  |  PERF6  |  PERF5  |  PERF4  |  PERF3  |  PERF2  |  PERF1  |  PERF0  |
---------------------------------------------------------------------------------------------------
CHECK BYTE				|  MSBIT  |   -     |    -    |    -    |    -    |  SFAIL  |  CFAIL  |  PPREQ  |
-------------------------------------------------------------------------------------------------*/
#define TINDX 0   // Table Byte Index.   Flags request-table (message, device, <tables to come>).

#define PINDX 1   /* Perform Byte Index. Flags a specific action to perform regarding the table.
									                       Right now just leds being switched on a device but guess
									                       CRUDE-functionality lives here down the road.*/
									                       	
#define CINDX 2   /* Check Byte Index.   Flags pull/push-request to server. If any errors accours,
																				 bits explaining the problem will be set and included in
																				 the response back to the client.*/
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

static inline uint8_t Termination_Message(const char *func, const char *cause) {
/*Errors detected of type fatal/termination.*/

	fprintf(stderr, "\nERROR | File [%s] Func [\"%s\"] Time [%s]" \
		"\nCAUSE | %s\nProgram will Terminate...\n",
		__FILE__, func, __DATE__, cause
	);
	return STERM;
}

static inline uint8_t Warning_Message(const char *func, const char *cause) {
/*Errors detected of type warning.*/

	fprintf(stderr, "\nWARNING | File [%s] Func [\"%s\"] Time [%s]" \
		"\nCAUSE | %s\nProgram will Terminate...\n",
		__FILE__, func, __DATE__, cause
	);
	return CWARN;
}

#define HEADER_FORM "\n%s\n%s\t\t\t%s\n%s\n\n"
#define Header_Border "--------------------------------------------------------------------------------------------------"
#define Render_Header(item, info) printf(HEADER_FORM, Header_Border, item, info, Header_Border);

#define ARRAY_SIZE(arry) (sizeof(arry)/sizeof(arry[0]))
#define PrintByte(byte) {for (int i = 7; 0 <= i; i--) {printf("%c", (byte & (1 << i)) ? '1' : '0');} printf("\n");}

#endif
