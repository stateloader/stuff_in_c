/*-------------------------------------------------------------------------------------------------------------------WRITER
Source-file containing all logic dealing with writing/appending to database(s).                 
/------------------------------------------------------------------------------------------------------------------------*/

#include "writer.h"

typedef struct WriteItem {
  const uint8_t flag;
  const char *filepath;
} write_item;

static write_item write_items[] = {
  {TMESG, "response/database/mesg.dat"},
  {TDVCE, "response/database/dvce.dat"}
};

static void database_trim(write_t *writer, uint16_t *state, uint16_t *error) {
/*Removes the PROTOCOL, or, rather trims it down for not including the package-data (isn't desired in the database.*/

  writer->size_appd -= POFFS;
  if (writer->append[writer->size_appd - 1] != DELIM) {
    *state |= (1 << ERROR); *error |= (1 << PDERR);
  }//last byte after trim should be a DELIM, else something gone south.
  return;
}

static void database_open(write_t *writer, uint16_t *state, uint16_t *error) {
/*A given database being open by fetch an item (with a mapped file-path) based on TBIDX in PROTOCOL. For now just two items
 *why this loop is rather pointless but in place for scaling when (if) more stuff to handle comes in place.*/

  if (*state & (1 << ERROR)) return;
  System_Message("Opens database.");

  for (size_t i = 0; i < ARRAY_SIZE(write_items); i++) {
    if (writer->protocol[TBIDX] & (1 << write_items[i].flag))
      writer->file = fopen(write_items[i].filepath, "a");
  } if (writer->file == NULL) {
    *state |= (1 << ERROR); *error |= (1 << FWERR);
  }//failed to open file.

  return;
}

static void database_push(write_t *writer, uint16_t *state, uint16_t *error)  {
/*Writing (appending) to database.*/

  if (*state & (1 << ERROR)) return;
  System_Message("Writing to database.");

  size_t size_push = fwrite(writer->append, sizeof(char), writer->size_appd, writer->file);
  if (size_push != writer->size_appd) {
    *state |= (1 << ERROR); *error |= (1 << FWERR);
  }//failed to append data to file.

  if (writer->file) fclose(writer->file);
  
  return;
}

void write_driver(write_t *writer, uint16_t *state, uint16_t *error) {

  database_trim(writer, state, error);
  database_open(writer, state, error);
  database_push(writer, state, error);

  return;
}