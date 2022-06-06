#include <stdio.h>
#include <stdlib.h>
#include "read.h"

static size_t entry_counter(read_t *reader) {

  size_t delims = 0;
  for (size_t i = 0; i < reader->data_size; i++)
    delims += reader->file_data[i] == DELIM ? 1 : 0;
  return (delims / PIPE);
}

static void tokenizer(read_t *reader) {

  reader->item_size = entry_counter(reader);
  printf("%ld", reader->item_size);
}

void read_driver(read_t *reader) {

  reader->file = fopen("resources/client.txt", "r");
  reader->file_data = calloc(FILE_BUFFER, sizeof(char));
  reader->data_size = fread(reader->file_data, sizeof(char), FILE_BUFFER, reader->file);

  fclose(reader->file);

  tokenizer(reader);
}
