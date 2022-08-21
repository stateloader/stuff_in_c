/*--------------------------------------------------------------------------------------------------------------------ERROR
If any errors is flagged it's going to be printed and dealt with here.
-------------------------------------------------------------------------------------------------------------------------*/

#include <stdlib.h>
#include "error.h"

static error_item error_items[] = {
  {PSERR, "Package",    "package size is corrupted."},
  {PTERR, "Package",    "package isn't nullterminated."},
  {PDERR, "Package",    "corrupted delimiter-format on package."},
  {IFERR, "System",     "failed to fetch an item which should be in place."},
  {CPERR, "System",     "copy failure."},
  {SDERR, "System",     "defaulted Switch-statement."},
  {RSERR, "Request",    "sent package is corrupted (control-size and send-size differ)."},
  {PBERR, "Response",   "MSB (one or more bytes) in PROTOCOL isn't set."},
  {PIERR, "Response",   "package (response) has its VALID-flag cleared (Something went south server-side)."},
  {MAERR, "Memory",     "failed to allocate memory."}
};

static void print_errors(uint16_t error) {
/*Prints error(s) detected.*/

  for (size_t i = 0; i < ARRAY_SIZE(error_items); i++) {
    if (error & (1 << error_items[i].flag))
    printf(ERROR_FORMAT, error_items[i].type, error_items[i].mesg);
  }
  exit(EXIT_FAILURE);
}

void error_driver(uint8_t state, uint16_t error) {

  if (state & (1 << ERROR))
    print_errors(error);
  System_Message("Session completed successfully.");
}
