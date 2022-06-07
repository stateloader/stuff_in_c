#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read.h"

#define FIELD_BUFFER 512

static void read_file_data(read_t *reader) {
 // 
  reader->file = fopen("resources/client.txt", "r");
  reader->file_data = calloc(MAX_FILE_DATA, sizeof(char));
  reader->file_size = fread(reader->file_data, sizeof(char), MAX_FILE_DATA, reader->file);
  
  fclose(reader->file);
}
//--------------------------------------------------------------------------------ALLOCS
static void alloc_model_cmods(read_t *reader) {
//  
  reader->model_cmods = malloc(sizeof(cmod_t *) * reader->model_count);
  for (size_t i = 0; i < reader->model_count; i++)
    reader->model_cmods[i] = malloc(sizeof(cmod_t) * reader->model_count);
}

static void fetch_model_count(read_t *reader, size_t interval) {
//
  for (size_t i = 0; i < reader->file_size; i++)
    reader->model_count += reader->file_data[i] == DELIM ? 1 : 0;
  reader->model_count = (reader->model_count / interval);
  alloc_model_cmods(reader);
}
/*
static void fetch_model_cmods_membr_data(read_t *reader) {
  
  size_t curr_field_size = 0;
  size_t curr_field_indx = 0;

  for (size_t i = 0; i < reader->file_size; i++) {
    field_buffer[curr_field_size] = reader->file_data[i];
    
    if (field_buffer[curr_field_size] == DELIM) {
      field_buffer[curr_field_size] = '\0';
      
    }
  }
}

*/
//---------------------------------------------------------------------------------//////
void read_driver(read_t *reader) {
//
  read_file_data(reader);
  fetch_model_count(reader, INTERVAL_CM);
  
//  alloc_model_cmods(reader);
  //fetch_model_cmods_membr_data(reader);

  free_driver(reader);
}

//--------------------------------------------------------------------------------FREES

void free_model_cmods(read_t *reader) {
  for (size_t i = 0; i < reader->model_count; i++)
    free(reader->model_cmods[i]);
  free(reader->model_cmods);
}

//--------------------------------------------------------------------------------//////

void free_driver(read_t *reader) {
  free_model_cmods(reader);
  free(reader->file_data); 
}