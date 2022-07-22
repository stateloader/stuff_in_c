/*--------------------------------------------------------------------------------------------------------------------ERROR
info info info
-------------------------------------------------------------------------------------------------------------------------*/

#include <stdlib.h>
#include "error.h"

static error_item error_items[] = {
  {PSERR, "Package",    "Package size is corrupted."},
  {PTERR, "Package",    "Package isn't nullterminated."},
  {PDERR, "Package",    "Corrupted delimiter-format on package."},
  {IFERR, "System",     "Failed to fetch an item which should be in place."},
  {CPERR, "System",     "Copy failure."},
  {SDERR, "System",     "Defaulted Switch-statement."},
  {RSERR, "Request",    "Sent package is corrupted (control-size and send-size differ)."},
  {PBERR, "Response",   "MSB (one or more bytes) in PROTOCOL isn't set."},
  {PIERR, "Response",   "Package (response) has its VALID-flag cleared (Something went south server-side)."},
  {MAERR, "Memory",     "Failed to allocate memory."}
};


static void print_errors(uint8_t status, uint16_t error) {
/*Prints error(s) detected.*/

  for (size_t i = 0; i < ARRAY_SIZE(error_items); i++) {
    if (error & (1 << error_items[i].flag))
    printf(ERROR_FORMAT, error_items[i].type, error_items[i].mesg);
  }
  exit(EXIT_FAILURE);
}

void error_driver(uint8_t status, uint16_t error) {

  if (status & (1 << ERROR))
    print_errors(status, error);
  System_Message("Session completed successfully.");
}