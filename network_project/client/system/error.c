/*--------------------------------------------------------------------------------------------------------------------ERROR
info info info
-------------------------------------------------------------------------------------------------------------------------*/

#include <stdlib.h>
#include "error.h"

static error_item error_items[] = {
  {PSERR, "Package",    "Wrong package size."},
  {PTERR, "Package",    "Package isn't terminated."},
  {PDERR, "Package",    "Corrupted delimiter-format on package."},
  {IIERR, "Iterator",   "Failed to fetch an item which should be in place."},
  {CPERR, "System",     "Copy failure."},
  {SDERR, "Switch",     "Defaulted switch-statement that shouldn't."},
  {RSERR, "Request",    "Failed to send package, size of size_pack and size_send differ."},
  {RRERR, "Response",   "Failed to receive package, size of size_pack and size_recv differ."},
  {PBERR, "Response",   "Protocol MSB not set."},
  {DCERR, "Response",   "Delimiter count corrupted."},
  {IVERR, "Response",   "Request invalid."},
  {MMERR, "Memory",     "Failed to allocate memory for table."}
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