#include <stdlib.h>
#include "read.h"
#include "write.h"
#include "database.h"

static read_t read_client(void) {

  read_t reader = {.rows = 0};
  read_driver(&reader);
  return reader;
}

void database_driver(void) {
  read_t reader = read_client();
}