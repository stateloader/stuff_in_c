#ifndef REQUEST_H_
#define REQUEST_H_

#include <stdint.h>
#include "cconfig.h"

#define Conn_View "CONNECT\tchoose by enter one of the commands below and hit enter."
#define Print_View_Item(item) printf("%s\n\n", item);

#define INFO_FORMAT "\n\tOoops: '%s' %s\n\n"
#define Info_Message(istr, imsg) printf(INFO_FORMAT, istr, imsg);

uint32_t request_driver(char *request, uint8_t *online);
  
#endif
