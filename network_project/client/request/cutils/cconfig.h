
#ifndef CCONFIG_H_
#define CCONFIG_H_
/*------------------------------------------------------------------------------------------------------------------------
                                                                                                MACRO KEYS, REQUEST_MODULE
info info info
------------------------------------------------------------------------------------------------------------------------*/
#define FLEE -1
#define FAIL 0
#define SUCC 1
//------------------------------------------------------------------------------------------------------------------------
#define RCLO "1"
#define RCSU "2"
//------------------------------------------------------------------------------------------------------------------------
#define LOGN 0
#define SIGU 1
//------------------------------------------------------------------------------------------------------------------------
#define CONN 0
#define MAIN 1
#define DATA 2
#define DVCE 3    
#define MSGE 4
#define EXIT 5
//------------------------------------------------------------------------------------------------------------------------
#define RBUFF 4096      // Request Buffer       - max allowed request data size.
#define MBUFF 512       // Message Buffer       - max allowed (request) message size.
#define DBUFF 32        // .... Buffer       - max allowed (request) (...) size.
//--------------------------------------------------------------------------------------------------------------"-GRAPHICS"

#define HEADER_FORM "%s\n%s\t\t%s\n%s\n\n"
#define Header_Bord "-----------------------------------------------------------------------------------------------------"
#define Print_Header(item, info) printf(HEADER_FORM, Header_Bord, item, info, Header_Bord);

#define WARNING_FORM "\t\t%s\n\n"
#define Print_Warning(warn) printf(WARNING_FORM, warn);

#define ScanItem(sitem) printf("%s: ", sitem);

//-------------------------------------------------------------------------------------------------------------------OTHER
#define DELIM '|'
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))
//-------------------------------------------------------------------------------------------------------------------OTHER

#endif