#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read.h"


static void read_file(read_t *reader) {
 // 
  reader->file = fopen("resources/client.txt", "r");
  reader->file_data = calloc(MAX_FILE_DATA, sizeof(char));
  reader->file_size = fread(reader->file_data, sizeof(char), MAX_FILE_DATA, reader->file);
  fclose(reader->file);
}

static void fetch_table_size(read_t *reader, size_t interval) {
//
  for (size_t i = 0; i < reader->file_size; i++)
    reader->entry_count += reader->file_data[i] == '|' ? 1 : 0;
  reader->entry_count = (reader->entry_count / interval);
}

void read_driver(read_t *reader) {
//
  read_file(reader);
  fetch_table_size(reader, INTERVAL_CM);
  printf("size: %ld\n\n", reader->entry_count);
  printf("data:\n%s\n\n", reader->file_data);
  free(reader->file_data);
}