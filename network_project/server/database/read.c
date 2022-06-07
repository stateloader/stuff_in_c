/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                SERVER TCP
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read.h"

#define MEMBER_BUFFER 512

//-----------------------------------------------------------------------------------------------current readfile (client).

static void read_file(read_t *reader) {

  reader->file = fopen("resources/client.txt", "r");
  reader->file_data = calloc(MAX_FILE_DATA, sizeof(char));
  reader->file_size = fread(reader->file_data, sizeof(char), MAX_FILE_DATA, reader->file);
  
  fclose(reader->file);
}

//--------------------------------------------------------------------------------------------current "set-stack" (client).

#define CMODUN 0
#define CMODPW 1

static void set_client_rows(read_t *reader) {

  for (size_t i = 0; i < reader->file_size; i++)
    reader->rows += (reader->file_data[i] == DELIM) ? 1 : 0;
  reader->rows = (reader->rows / INTERVAL_CM);
}

static void set_client_table(read_t *reader) {
  
  set_client_rows(reader);
  reader->table_client = malloc(sizeof(cmod_t) * reader->rows);

  for (size_t i = 0; i < reader->rows; i++) {
    cmod_t rows = {.id = i};
    reader->table_client[i] = rows;
  }
}

static void set_client_data(read_t *reader) {

  set_client_table(reader);

  char byte = ' ';
  size_t memidx = 0, member = 0, modrow = 0;

  for (size_t i = 0; i < reader->file_size; i++) {
    byte = reader->file_data[i];

    switch(member) {
    case CMODUN:
      if (byte != DELIM) {
        reader->table_client[modrow].username[memidx] = byte;
        memidx++;
      } else {
        reader->table_client[modrow].username[memidx] = '\0';
        printf("idx[%ld] username:  %s\n", modrow, reader->table_client[modrow].username);
        memidx = 0, member = CMODPW;
      }
      break;

    case CMODPW:
      if (byte != DELIM) {
        reader->table_client[modrow].password[memidx] = byte;
        memidx++;
      } else {
        reader->table_client[modrow].password[memidx] = '\0';
        printf("idx[%ld] username:  %s\n", modrow, reader->table_client[modrow].password);
        memidx = 0, member = CMODUN, modrow++;
      }
      break;
    }
  }
}
//------------------------------------------------------------------------------------------------current driver (client).
void read_driver(read_t *reader) {

  read_file(reader);
  set_client_data(reader);
  free_driver(reader);
}
//---------------------------------------------------------------------------------------------current free-logic (client).

void free_driver(read_t *reader) {
  free(reader->file_data); 
  free(reader->table_client);
}