#include <stdio.h>
#include <stdlib.h>
#include "read.h"

size_t read_driver(char *content) {

  size_t size = 0;

  FILE *read_file = fopen("resources/client.txt", "r");

  size = fread(content, sizeof(char), FSIZE_LIMIT, read_file);
  if (!size) {
    printf("fi pajj size");
    free(content);
    fclose(read_file);
    exit(EXIT_FAILURE);
  }
  fclose(read_file);
  return size;
}
