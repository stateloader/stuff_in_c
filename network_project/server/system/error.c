#include "error.h"


#define ERROR_FORMAT "\n-- Error -- %s, %s\n            Issue orginates from %s\n\n"

typedef struct ErrorItem {
  const uint16_t flag;
  const char *type;
  const char *mesg;
} error_item;


/*-------------------------------------------------------------------------------------------------------------------------
BIT(N)                                    |    15   |    14   |    13   |    12   |    11   |    10   |    9    |    8    |
ERROR HIGH BYTE                           |    -    |    -    |    -    |    -    |    -    |    -    |    -    |  RPERR  |
---------------------------------------------------------------------------------------------------------------------------
BIT(N)                                    |    7    |    6    |    5    |    4    |    3    |    2    |    1    |    0    |
ERROR HIGH BYTE                           |    -    |    -    |    -    |    -    |  CAERR  |  CLERR  |  SCERR  |  SSERR  |
-------------------------------------------------------------------------------------------------------------------------*/

static error_item error_items[] = {
  {SSERR, "Socket",     "Failed to create server-socket."},
  {SCERR, "Connection", "Failed to create server connection."},
  {CLERR, "Client",     "Failed to listening for clients."},
  {CAERR, "Client",     "Failed to accepting client."},
  {RPERR, "Receive",    "Received Package size to small."}
};

void error_driver(uint16_t error, char *location) {
  for (size_t i = 0; i < ARRAY_SIZE(error_items); i++) {
    if (error & (1 << error_items[i].flag)) {
      printf(ERROR_FORMAT, error_items[i].type, error_items[i].mesg, location);
    }
  }
}