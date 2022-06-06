
#include <stdio.h>
#include <stdlib.h>
#include "read.h"

static size_t item_count(char *content, size_t size) {
  size_t pipes = 0;
  for (size_t i = 0; i < size; i++)
    pipes += content[i] == DELIM ? 1 : 0;
  return (pipes / 6);
}

static void tokenazier(char *content, size_t size) {

  size_t items = item_count(content, size);
  printf("%ld", items);
}

size_t read_driver(char *content) {

  FILE *file_reader = fopen("resources/client.txt", "r");
  size_t size = fread(content, sizeof(char), FILE_BUFFER, file_reader);
  fclose(file_reader); 
  tokenazier(content, size);
  return size;
}