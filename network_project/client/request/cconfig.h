
#ifndef CCONFIG_H_
#define CCONFIG_H_

#define SUCC 1
#define FAIL 0
/*------------------------------------------------------------------------------------------------------------------------
                                                                                                MACRO KEYS, REQUEST_MODULE
info info info
------------------------------------------------------------------------------------------------------------------------*/
//------item

#define LOGN 0
#define SIGU 1

#define CONN 0
#define MAIN 1
#define DATA 2
#define DVCE 3    
#define MSGE 4
#define EXIT 5

//------------------------------------------------------------------------------------------------------------------------

#define RBUFF 4096      // Request Buffer       - max allowed request data size.
#define MBUFF 512       // Message Buffer       - max allowed (request) message size.
#define DBUFF 32       // Message Buffer       - max allowed (request) message size.

//-------------------------------------------------------------------------------------------------------------------OTHER

#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

#endif