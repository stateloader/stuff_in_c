#include <stdio.h>
#include <stdlib.h>
#include "read.h"

#define LINEBUFF 512
//static fetch_memory
/*
int main() {
   char string[50] = "Hello! We are learning about strtok";
   // Extract the first token
   char * token = strtok(string, " ");
   // loop through the string to extract all other tokens
   while( token != NULL ) {
      printf( " %s\n", token ); //printing each token
      token = strtok(NULL, " ");
   }
   return 0;
}
*/
static void fetch_tokens(read_t *reader, size_t entryline)
{
  char token = strtok(entryline, '|');
}

static void fetch_tables(read_t *reader, size_t interval)
{
  char entryline[LINEBUFF] = {0};

  for (size_t i = 0; i < reader->file_size; i++) { 

    tokbuff[i] = reader->file_size[i];
    reader->count_entries += reader->file_data[i] == '|' ? 1 : 0;

    if (reader->count_entries % interval == 0) {
      fetch_tokens(reader, entryline);
    }
  reader->count_entries = (reader->count_entries / interval);
}

void read_driver(read_t *reader)
{
  reader->file = fopen("resources/client.txt", "r");
  reader->file_data = calloc(FILE_BUFFER, sizeof(char));                                  // calloceras bara en gång, memsettas vid varje kall.
  reader->file_size = fread(reader->file_data, sizeof(char), FILE_BUFFER, reader->file);

  fclose(reader->file);
  fetch_tables(reader, INTERVAL_CM);
  printf("size: %ld\n", reader->count_entries);
}

/*
  reader->client_model = (cmod_t **) malloc(reader->count_entries * sizeof(cmod_t *))
  for (size_t i = 0; i < reader->count_entries; i++)
    client->client_model[i] = malloc(sizeof(cmod_t));
*/
