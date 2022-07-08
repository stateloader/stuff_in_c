#ifndef ERROR_H_
#define ERROR_H_

#include "../configs.h"

/*-------------------------------------------------------------------------------------------------------------------------
BIT(N)                                    |    15   |    14   |    13   |    12   |    11   |    10   |    9    |    8    |
ERROR HIGH BYTE                           |    -    |    -    |    -    |    -    |    -    |    -    |    -    |  RPERR  |
---------------------------------------------------------------------------------------------------------------------------
BIT(N)                                    |    7    |    6    |    5    |    4    |    3    |    2    |    1    |    0    |
ERROR HIGH BYTE                           |    -    |    -    |    -    |    -    |  CAERR  |  CLERR  |  SCERR  |  SSERR  |
-------------------------------------------------------------------------------------------------------------------------*/

/*
#define SSERR 0                             // Server Socket Error.
#define SCERR 1                             // Server Connection Error.
#define CLERR 2                             // Server Listening (On Client) Error.
#define CAERR 3

#define RPERR 8                             // Received Package Error;

*/
void error_driver(uint16_t error_flag, char *location);

#endif

