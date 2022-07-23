/*-------------------------------------------------------------------------------------------------------------ERROR DRIVER
                                                                                          
-------------------------------------------------------------------------------------------------------------------------*/
#include "error.h"

static error_item error_items[] = {
  {SSERR, "SOCKET",     "Failed to create server-socket."},
  {SCERR, "CONNECTION", "Failed to create server connection."},
  {CLERR, "client",     "Failed to listening for clients."},
  {CAERR, "Client",     "Failed to accepting client."},
  {SWERR, "SWITCH",     "Switch statement has reached default."},
  {ITERR, "ITERATION",  "Failed (where a match should has been vailable)."},
  {FOERR, "FILE",       "Failed to open file."},
  {RWERR, "FILE",       "Failed to read/write to file"},
  {RSERR, "RECEIVE",    "Received package is below lowest accepted size."},
  {RTERR, "RECEIVE",    "Received package isn't nullterminated."},
  {RUERR, "RECEIVE",    "Received package has a corrupted protocol."},
  {PCERR, "PACKAGE",    "Failed to copy package."},
  {FWERR, "File",       "Failed to write (append) to file."},
  {FRERR, "File",       "Failed to read from file."},
  {DDERR, "DELIMITER",  "Delimiter error."},
  {RCERR, "RESPONSE",   "Failed to response client."}
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