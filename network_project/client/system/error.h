#ifndef ERROR_H_
#define ERROR_H_

#include "../configs.h"

/*-----------------------------------------------------------------------------------------------------------error low byte
BIT(N)                                    |    7    |    6    |    5    |    4    |    3    |    2    |    1    |    0    |
CONSTANT                                  |  SDERR  |    -    |  IIERR  |  DMERR  |  PTERR  |  PSERR  |  COERR  |  SOERR  |
-------------------------------------------------------------------------------------------------------------------------*/

void error_driver(uint16_t error_flag);

#endif