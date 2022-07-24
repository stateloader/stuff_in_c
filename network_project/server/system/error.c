/*-------------------------------------------------------------------------------------------------------------ERROR DRIVER
If any errors is flagged it's going to be printed and dealt with here.                              
-------------------------------------------------------------------------------------------------------------------------*/
#include "error.h"

static error_item error_items[] = {
  {SCERR, "Connection", "Connection lost."},
  {CLERR, "Client",     "Failed to listening for clients."},
  {CAERR, "Client",     "Failed to accepting client."},
  {PSERR, "Package",    "Package size is corrupted."},
  {PTERR, "Package",    "Package isn't nullterminated."},
  {PDERR, "Package",    "Corrupted delimiter-format on package."},
  {PBERR, "Package",    "MSB (one or more bytes) in PROTOCOL isn't set."},
  {PIERR, "Package",    "Package (response) has its VALID-flag cleared (Something went south client-side)."},
  {IFERR, "System",     "Failed to fetch an item during iteration (wich should be in place)."},
  {CPERR, "System",     "Corrupted delimiter-format on package."},
  {SDERR, "System",     "Defaulted Switch-statement."},
  {FWERR, "System",     "Failed to write (append) to file."},
  {FRERR, "System",     "Failed to read from file."},
};

void error_driver(uint16_t status, uint16_t error) {

  if (status & (1 << ERROR)) {
    for (size_t i = 0; i < ARRAY_SIZE(error_items); i++) {
      if (error & (1 << error_items[i].flag))
      printf(ERROR_FORMAT, error_items[i].type, error_items[i].mesg);
    }
  } else {
    System_Message("Session completed successfully.");
  }
}