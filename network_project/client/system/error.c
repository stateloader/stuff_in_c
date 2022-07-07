#include "error.h"

/*-------------------------------------------------------------------------------------------------------------------------
BIT(N)                                    |    15   |    14   |    13   |    12   |    11   |    10   |    9    |    8    |
ERROR HIGH BYTE                           |  SDERR  |    -    |  MMERR  |  IVERR  |  DCERR  |  PBERR  |  RRERR  |  RSERR  |
---------------------------------------------------------------------------------------------------------------------------
BIT(N)                                    |    7    |    6    |    5    |    4    |    3    |    2    |    1    |    0    |
ERROR LOW BYTE                            |  SDERR  |  TPERR  |  IIERR  |  PDERR  |  PTERR  |  PSERR  |  COERR  |  SOERR  |
---------------------------------------------------------------------------------------------------------------------------
#define SOERR 0                           // Socket error, we didn't even manage to create a socket.                          
#define COERR 1                           // Connect error, couldn't connect to the server.
#define PSERR 2                           // Package size error, sizes between sent and created doesn't match. 
#define PTERR 3                           // Package (not) terminated error, package isn't nullterminated.
#define PDERR 4                           // The supposed amount the entry's delimiter-constant supposed to be is wrong.
#define IIERR 5                           // Failed to fetch an item (wich should be in place).
#define TPERR 6                           // <until filling for now>
#define SDERR 7                           // A given switch-statment has reach default (for some reason).
#define RSERR 8                           // Failed to send package, size of size_pack and size_send differ.
#define RRERR 9                           // Failed to receive package, size of size_pack and size_recv differ.
#define PBERR 10                          // Protocol Byte wrong format.
#define DCERR 11                          // Delimitier count corrupted.
#define IVERR 12                          // Server has cleared VALID-flag.
#define MMERR 13                          // Failed to allocate memory for table.
*/

#define ERROR_FORMAT "\n-- Error -- %s, %s\n            Issue orginates from %s\n\n"

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

void error_driver(uint16_t error, char *location) {

  for (size_t i = 0; i < ARRAY_SIZE(error_items); i++) {
    if (error & (1 << error_items[i].flag)) {
      printf(ERROR_FORMAT, error_items[i].type, error_items[i].mesg, location);
    }
  }
}