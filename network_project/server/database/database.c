#include <stdlib.h>
#include "read.h"
#include "write.h"
#include "database.h"

static read_t database_client_read(void) {

  read_t reader = {.data_size = 0};
  read_driver(&reader);

  printf("raw_data\n\n%s\n", reader.file_data);

  free(reader.file_data);

  return reader;
}

void database_driver(void) {
  database_client_read();
}
