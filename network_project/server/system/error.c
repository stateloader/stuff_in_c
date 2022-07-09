/*-------------------------------------------------------------------------------------------------------------ERROR DRIVER
Macros implemented reg                                                                                                   
/------------------------------------------------------------------------------------------------------------------------*/

#include "error.h"

#define ERROR_FORMAT "\n-- Error [%s] -- %s\n\n"

typedef struct ErrorItem {
  const uint16_t flag;
  const char *type;
  const char *mesg;
} error_item;

/*-------------------------------------------------------------------------------------------------------------------------
BIT(N)                                    |    15   |    14   |    13   |    12   |    11   |    10   |    9    |    8    |
ERROR HIGH BYTE                           |  RCERR  |  DDERR  |  FRERR  |  FWERR  |  PCERR  |  RUERR  |  RTERR  |  RSERR  |
---------------------------------------------------------------------------------------------------------------------------
BIT(N)                                    |    7    |    6    |    5    |    4    |    3    |    2    |    1    |    0    |
ERROR HIGH BYTE                           |  RWERR  |  FOERR  |  ITERR  |  SWERR  |  CAERR  |  CLERR  |  SCERR  |  SSERR  |
-------------------------------------------------------------------------------------------------------------------------*/


static error_item error_items[] = {
  {SSERR, "SOCKET",     "Failed to create server-socket."},
  {SCERR, "CONNECTION", "Failed to create server connection."},
  {CLERR, "CLIENT",     "Failed to listening for clients."},
  {CAERR, "CLIENT",     "Failed to accepting client."},
  {SWERR, "SWITCH",     "Switch statement has reached default."},
  {ITERR, "ITERATION",  "Failed (where a match should has been vailable)."},
  {FOERR, "FILE",       "Failed to open file."},
  {RWERR, "FILE",       "Failed to read/write to file"},
  {RSERR, "RECEIVE",    "Received package is below lowest accepted size."},
  {RTERR, "RECEIVE",    "Received package isn't nullterminated."},
  {RUERR, "RECEIVE",    "Received package has a corrupted protocol."},
  {PCERR, "PACKAGE",    "Failed to copy package."},
  {FWERR, "WRITE FILE", "Failed to write (append) to file."},
  {FRERR, "READ FILE",  "Failed to read from file."},
  {DDERR, "DELIMITER",  "Delimiter error."},
  {RCERR, "RESPONSE",   "Failed to response client."}
};

void error_driver(uint16_t status, uint16_t error) {

  if (status & (0 << ERROR)) return;

  for (size_t i = 0; i < ARRAY_SIZE(error_items); i++) {
    if (error & (1 << error_items[i].flag))
      printf(ERROR_FORMAT, error_items[i].type, error_items[i].mesg);
  }
}