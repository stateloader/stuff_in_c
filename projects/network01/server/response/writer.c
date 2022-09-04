/*-------------------------------------------------------------------------------------------WRITER
Logic dealing with request ending up in writing to file.
-------------------------------------------------------------------------------------------------*/

#include "writer.h"

//'write_item'-whereabouts in place for scalability when/if more databases come in place.

typedef struct WriteItem {
  const uint8_t flag;
  const char *filepath;
} write_item;

static write_item write_items[] = {
  {TMESG, "response/database/mesg.dat"},
  {TDVCE, "response/database/dvce.dat"}
};

static void database_trim(write_t *writer) {
/*Removes 'protocol' by decrement the size of the append-string.*/

  writer->size_push -= POFFS;
  if (writer->append[writer->size_push - 1] != DELIM)
 		System_Message("[Error to catch]: append-size doesen't end with delim.");
  return;
}

static void database_open(write_t *writer) {
 
  for (size_t i = 0; i < ARRAY_SIZE(write_items); i++) {
    if (writer->protocol[TINDX] & (1 << write_items[i].flag))
      writer->file = fopen(write_items[i].filepath, "a");
  }
  if (writer->file == NULL)
 		System_Message("[Error to catch]: file not found append.");
 		
  return;
}

static void database_push(write_t *writer)  {
/*Writing (appending) to database.*/

  size_t size_push = fwrite(writer->append, sizeof(char), writer->size_push, writer->file);
  if (size_push != writer->size_push)
 		System_Message("[Error to catch]: bytes written not the same as stored in size_appnd.");
  
  if (writer->file) fclose(writer->file);
  
  return;
}

void write_driver(write_t *writer) {

  database_trim(writer);
  database_open(writer);
  database_push(writer);

  return;
}
