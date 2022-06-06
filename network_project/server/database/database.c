
#include <stdlib.h>
#include "read.h"
#include "write.h"
#include "database.h"

void database_client_driver(char **content) {

	*content = calloc(FILE_BUFFER, sizeof(char));
  read_driver(*content);
  free(*content);
}