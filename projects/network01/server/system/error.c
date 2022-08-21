/*-------------------------------------------------------------------------------------------------------------ERROR DRIVER
If any errors is flagged it's going to be printed and dealt with here.                              
-------------------------------------------------------------------------------------------------------------------------*/
#include "error.h"

static error_item error_items[] = {
  {SCERR, "Connection", "connection lost."},
  {CLERR, "Client",     "failed to listening for clients."},
  {CAERR, "Client",     "failed to accepting client."},
  {PSERR, "Package",    "package size is corrupted (but as for current conf, prob disconnecting client)."},
  {PTERR, "Package",    "package isn't nullterminated."},
  {PDERR, "Package",    "corrupted delimiter-format on package."},
  {PBERR, "Package",    "MSB (one or more bytes) in PROTOCOL isn't set."},
  {PIERR, "Package",    "package (response) has its VALID-flag cleared (Something went south client-side)."},
  {IFERR, "System",     "failed to fetch an item during iteration (wich should be in place)."},
  {CPERR, "System",     "corrupted delimiter-format on package."},
  {SDERR, "System",     "defaulted Switch-statement."},
  {FWERR, "System",     "failed to write (append) to file."},
  {FRERR, "System",     "failed to read from file."},
};

void error_driver(uint16_t *status, uint16_t *error) {

  for (size_t i = 0; i < ARRAY_SIZE(error_items); i++) {
    if (*error & (1 << error_items[i].flag))
    printf(ERROR_FORMAT, error_items[i].type, error_items[i].mesg);
  }
  *status &= ~(1 << ERROR); *error = 0x00;
}