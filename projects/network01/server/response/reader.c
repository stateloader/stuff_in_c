/*-------------------------------------------------------------------------------------------READER
Logic dealing with requests ending up in reading from file.
-------------------------------------------------------------------------------------------------*/

#include "reader.h"

//'read_item'-whereabouts in place for scalability when/if more databases come in place.

typedef struct ReadItem {
  const uint8_t flag;
  const char *filepath;
} read_item;

static read_item read_items[] = {
  {TMESG, "response/database/mesg.dat"},
  {TDVCE, "response/database/dvce.dat"}
};

static void database_open(read_t *reader) {

  for (size_t i = 0; i < ARRAY_SIZE(read_items); i++) {
    if (reader->protocol[TINDX] & (1 << read_items[i].flag))
      reader->file = fopen(read_items[i].filepath, "r");
  }
  if (reader->file == NULL)
 		System_Message("[Error to catch]: file not found read.");
  return;
}

static void database_pull(read_t *reader)  {
/*Reading from database.*/

  reader->size_pull = fread(reader->read, sizeof(char), RBUFF, reader->file);
  
  if (reader->size_pull < 1)
 		System_Message("[Error to catch]: did't read any data from 'fread'.");
  
  if (reader->file) fclose(reader->file);

  return;
}

void read_driver(read_t *reader) {

  database_open(reader);
  database_pull(reader);
  
  return;
}
