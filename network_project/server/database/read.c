#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read.h"

#define FIELD_BUFFER 512

static void read_file(read_t *reader) {
 // 
  reader->file = fopen("resources/client.txt", "r");
  reader->file_data = calloc(MAX_FILE_DATA, sizeof(char));
  reader->file_size = fread(reader->file_data, sizeof(char), MAX_FILE_DATA, reader->file);
  
  fclose(reader->file);
}

static void fetch_entry_count(read_t *reader, size_t interval) {
//
  for (size_t i = 0; i < reader->file_size; i++)
    reader->model_count += reader->file_data[i] == DELIM ? 1 : 0;
  reader->model_count = (reader->model_count / interval);
}

static void alloc_cmodel_memory(read_t *reader) {
//
  char field_buffer[FIELD_BUFFER];
  size_t current_field_size = 0;

  reader->model_sizes = malloc(sizeof(size_t *) * reader->model_count);  
  reader->client_models = malloc(sizeof(cmod_t *) * reader->model_count);
  

  for (size_t i = 0; i < reader->model_count; i++) {
    reader->model_sizes[i] = (i + 5);
    reader->client_models[i] = malloc(sizeof(cmod_t) * reader->model_count);
  }
}

void read_driver(read_t *reader) {
//
  read_file(reader);

  fetch_entry_count(reader, INTERVAL_CM);
  alloc_cmodel_memory(reader);

  free_driver(reader);
}

void free_model_cmods(read_t *reader) {
  for (size_t i = 0; i < reader->model_count; i++)
    free(reader->client_models[i]);
  free(reader->client_models);
}

void free_model_sizes(read_t *reader) {
  free(reader->model_sizes);
}

void free_driver(read_t *reader) {
  free_model_cmods(reader);
  free_model_sizes(reader);
  free(reader->file_data);
  
}
/*
  for (size_t i = 0; i < reader->model_count; i++) {
    printf("%ld\n", reader->model_sizes[i]);
  }

  printf("size: %ld\n\n", reader->entry_count);
  printf("data:\n%s\n\n", reader->file_data);
*/