
/*------------------------------------------------------------------------------------SERVER DRIVER

-------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------READER
Source-file containing all logic dealing with reading from database(s).                                                             
/------------------------------------------------------------------------------------------------------------------------*/
#include "reader.h"

static read_item read_items[] = {
  {TMESG, "response/database/mesg.dat"},
  {TDVCE, "response/database/dvce.dat"}
};

static void database_open(read_t *reader) {
/*For now just two items why this loop isn't really needed but it's in place for scaling when (if) more stuff to handle
 *is in place.*/

  System_Message("opens the file.");

  for (size_t i = 0; i < ARRAY_SIZE(read_items); i++) {
    if (reader->protocol[TINDX] & (1 << read_items[i].flag))
      reader->file = fopen(read_items[i].filepath, "r");
  }
  return;
}

static void database_pull(read_t *reader)  {
/*Reading content from the (a) database.*/

  reader->size_cont = fread(reader->content, sizeof(char), RBUFF, reader->file);
  if (reader->file) fclose(reader->file);

  return;
}

void read_driver(read_t *reader) {

  database_open(reader);
  database_pull(reader);
  
  return;
}
