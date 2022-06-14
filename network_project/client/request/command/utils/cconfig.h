
#ifndef CCONFIG_H_
#define CCONFIG_H_
/*------------------------------------------------------------------------------------------------------------------------
                                                                                                MACRO KEYS, REQUEST_MODULE
info info info
------------------------------------------------------------------------------------------------------------------------*/
#define FAIL 0
#define SUCC 1
/*---------------------------------------------------------------------------------------"PROTOCOL" endstring client/server

bit                     |    7    |    6    |    5    |    4    |    3    |     2    |     1     |     0     |
constant                |  RWBIT  |  SLCT2  |  SLCT1  |  SLCT0  |  MMSGE  |   MDVCE  |   MDATA   |   MUSER   |
------------------------------------------------------------------------------------------------------------------------*/
#define RULO 0b00000001 // Request User Login
#define RUSU 0b10000001 // Request User Signup

#define RDTP 0b00010010 // Request Data Temperature
#define RDMG 0b00100010 // Request Data Messages

#define RADR 0b10010100 // Request Activate Device Red (LED)
#define RADB 0b10100100 // Request Activate Device Blue (LED)
#define RADG 0b11000100 // Request Activate Device Green (LED)

#define RWMG 0b10011000  // Request Write Message
//------------------------------------------------------------------------------------------------------------------commit
#define LOGN 0
#define SIGU 1
//------------------------------------------------------------------------------------------------------------------------
#define FLEE -2
#define QUIT -1
#define MAIN 0
//------------------------------------------------------------------------------------------------------------------------
#define RBUFF 4096
#define CBUFF 512
//--------------------------------------------------------------------------------------------------------------"-GRAPHICS"
#define HEADER_FORM "%s\n%s\t\t%s\n%s\n\n"
#define Header_Bord "-----------------------------------------------------------------------------------------------------"
#define Print_Header(item, info) printf(HEADER_FORM, Header_Bord, item, info, Header_Bord);

#define WARNING_FORM "\t\t%s\n\n"
#define Print_Warning(warn) printf(WARNING_FORM, warn);

//-------------------------------------------------------------------------------------------------------------------OTHER
#define DELIM '|'
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))
//-------------------------------------------------------------------------------------------------------------------OTHER

#endif