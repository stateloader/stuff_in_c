/*-------------------------------------------------------------------------------------------------------------------READER
Source-file containing all logic dealing with reading from database(s).                                                             
/------------------------------------------------------------------------------------------------------------------------*/
#include "reader.h"

static read_item read_items[] = {
  {TMESG, "response/database/mesg.dat"},
  {TDVCE, "response/database/dvce.dat"}
};

static void database_open(read_t *reader, uint16_t *state, uint16_t *error) {
/*For now just two items why this loop isn't really needed but it's in place for scaling when (if) more stuff to handle
 *is in place.*/

  if (*state & (1 << ERROR)) return;
  System_Message("opens the file.");

  for (size_t i = 0; i < ARRAY_SIZE(read_items); i++) {
    if (reader->protocol[TBIDX] & (1 << read_items[i].flag))
      reader->file = fopen(read_items[i].filepath, "r");
  }
  if (reader->file == NULL) {
    *state |= (1 << ERROR); *error |= (1 << FRERR);
  }//failed to open file.

  return;
}

static void database_pull(read_t *reader, uint16_t *state, uint16_t *error)  {
/*Reading content from the (a) database.*/

  if (*state & (1 << ERROR)) return;
  System_Message("reading from database.");

  reader->size_cont = fread(reader->content, sizeof(char), RBUFF, reader->file);
  if (reader->size_cont <= 0) {
    *state |= (1 << ERROR); *error |= (1 << FRERR);
  }//failed to read data from file.
  if(reader->file) fclose(reader->file);

  return;
}

void read_driver(read_t *reader, uint16_t *state, uint16_t *error) {

  database_open(reader, state, error);
  database_pull(reader, state, error);
  
  return;
}