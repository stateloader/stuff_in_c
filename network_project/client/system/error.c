#include <stdlib.h>
#include "error.h"

/*-------------------------------------------------------------------------------------------------------------------------
BIT(N)                                    |    15   |    14   |    13   |    12   |    11   |    10   |    9    |    8    |
ERROR HIGH BYTE                           |  SDERR  |    -    |  MMERR  |  IVERR  |  DCERR  |  PBERR  |  RRERR  |  RSERR  |
---------------------------------------------------------------------------------------------------------------------------
BIT(N)                                    |    7    |    6    |    5    |    4    |    3    |    2    |    1    |    0    |
ERROR LOW BYTE                            |  SDERR  |  CPERR  |  IIERR  |  PDERR  |  PTERR  |  PCERR  |  SCERR  |  SSERR  |
-------------------------------------------------------------------------------------------------------------------------*/

#define ERROR_FORMAT "\n-- Error [%s] -- %s\n\n"

typedef struct ErrorItem {
  const uint16_t flag;
  const char *type;
  const char *mesg;
} error_item;

static error_item error_items[] = {
  {SSERR, "Socket",     "Failed to create create client-socket."},                                //0
  {SCERR, "Connection", "Failed to connect to server."},                                          //1
  {PSERR, "Package",    "Wrong package size."},                                                   //2
  {PTERR, "Package",    "Package isn't terminated."},                                             //3
  {PDERR, "Package",    "Corrupted delimiter-format on package."},                                //4
  {IIERR, "Iterator",   "Failed to fetch an item which should be in place."},                     //5
  {CPERR, "System",     "Copy Failure."},                                                         //6
  {SDERR, "Switch",     "Defaulted switch-statement that shouldn't."},                            //7
  {RSERR, "Request",    "Failed to send package, size of size_pack and size_send differ."},       //8
  {RRERR, "Response",   "Failed to receive package, size of size_pack and size_recv differ."},    //9
  {PBERR, "Response",   "Protocol byte not unsigned."},                                           //10
  {DCERR, "Response",   "Delimiter count corrupted."},                                            //11
  {IVERR, "Response",   "Request invalid."},                                                      //12
  {MMERR, "Memory",     "Failed to allocate memory for table."}                                   //13
};

void error_driver(uint8_t status, uint16_t error) {
  if (status & (0 << ERROR)) return;

  for (size_t i = 0; i < ARRAY_SIZE(error_items); i++) {
    if (error & (1 << error_items[i].flag))
      printf(ERROR_FORMAT, error_items[i].type, error_items[i].mesg);
  }
  exit(EXIT_FAILURE);
}