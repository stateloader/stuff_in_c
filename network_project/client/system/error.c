#include <stdlib.h>
#include "error.h"

/*-------------------------------------------------------------------------------------------------------------------------
BIT(N)                                    |    15   |    14   |    13   |    12   |    11   |    10   |    9    |    8    |
ERROR HIGH BYTE                           |  SDERR  |    -    |  MMERR  |  IVERR  |  DCERR  |  PBERR  |  RRERR  |  RSERR  |
---------------------------------------------------------------------------------------------------------------------------
BIT(N)                                    |    7    |    6    |    5    |    4    |    3    |    2    |    1    |    0    |
ERROR LOW BYTE                            |  SDERR  |  TPERR  |  IIERR  |  PDERR  |  PTERR  |  PSERR  |  COERR  |  SOERR  |
-------------------------------------------------------------------------------------------------------------------------*/

#define ERROR_FORMAT "\n-- Error -- %s, %s\n\n"

typedef struct ErrorItem {
  const uint16_t flag;
  const char *type;
  const char *mesg;
} error_item;

static error_item error_items[] = {
  {SOERR, "Socket",     "Failed to create Socket."},
  {COERR, "Connection", "Failed to create Socket."},
  {PSERR, "Package",    "Wrong package size."},
  {PTERR, "Package",    "Package isn't terminated."},
  {PDERR, "Package",    "Wrong delimiter-format on package."},
  {IIERR, "Iterator",   "Failed to fetch an item which should be in place."},
  {SDERR, "Switch",     "Defaulted switch-statement that shouldn't."},
  {RSERR, "Request",    "Failed to send package, size of size_pack and size_send differ."},
  {RRERR, "Response",   "Failed to receive package, size of size_pack and size_recv differ."},
  {PBERR, "Response",   "Protocol byte not unsigned."},
  {DCERR, "Response",   "Delimiter count corrupted."},
  {IVERR, "Response",   "Request invalid."},
  {MMERR, "Memory",     "Failed to allocate memory for table."}
};

void error_driver(uint16_t error) {

  for (size_t i = 0; i < ARRAY_SIZE(error_items); i++) {
    if (error & (1 << error_items[i].flag)) {
      printf(ERROR_FORMAT, error_items[i].type, error_items[i].mesg);
    }
  }
  exit(EXIT_FAILURE);
}