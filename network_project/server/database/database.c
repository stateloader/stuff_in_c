#include <stdlib.h>
#include "read.h"
#include "write.h"
#include "database.h"

void database_client_driver(char **content) {

	*content = calloc(FSIZE_LIMIT, sizeof(char));
  printf("size %ld\n", read_driver(*content));
  printf("content\n\n%s\n", *content);
  free(*content);
}

void database_sample_driver(char **content) {

	*content = calloc(FSIZE_LIMIT, sizeof(char));
  free(*content);
}
