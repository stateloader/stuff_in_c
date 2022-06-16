#ifndef SERVER_H_
#define SERVER_H_

#include <stdint.h>
#include "drivers/sconfig.h"

//----------------------------------------------------------------------------------------------------------------------*/

typedef struct Server {
  uint8_t status;
  int32_t size_file;
  FILE *dbfile[SBUFF];
  char recieved[SBUFF];
} server_t;

#endif