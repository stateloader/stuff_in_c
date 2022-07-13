/*-------------------------------------------------------------------------------------------------------------------WRITER
Any request from client where pushing/writing/inserting anything to the server beeing thrown here by the response-driver.                                                                             
/------------------------------------------------------------------------------------------------------------------------*/

#include "writer.h"

static void database_trim(write_t *writer, uint16_t *state, uint16_t *error) {
/*Removes the PROTOCOL (rather trims down the package-size for not including it). Not desired in the database.*/

  writer->size_appd -= POFFS;
  if (writer->append[writer->size_appd - 1] != DELIM) {
    *state |= (1 << ERROR); *error |= (1 << DDERR);
  }//Last byte after trim should be a DELIM, else something gone south. 
  return;
}

static write_item write_items[] = {
  {TMESG, "response/database/mesg.dat"},
  {TDVCE, "response/database/dvce.dat"}
};

static void database_open(write_t *writer, uint16_t *state, uint16_t *error) {
/*For now just two items why this loop isn't really needed but it's in place for scaling when (if) more stuff to handle
 *comes in place*/

  if (*state & (1 << ERROR)) return;
  System_Message("Opens database.");

  for (size_t i = 0; i < ARRAY_SIZE(write_items); i++) {
    if (writer->protocol[TBIDX] & (1 << write_items[i].flag))
      writer->file = fopen(write_items[i].filepath, "a");
  } if (writer->file == NULL) {
    *state |= (1 << ERROR); *error |= (1 << FOERR);
  }//Failed to open file.
  return;
}

static void database_push(write_t *writer, uint16_t *state, uint16_t *error)  {
/*Writing (appending) to database*/

  if (*state & (1 << ERROR)) return;
  System_Message("Writing to database.");

  size_t size_push = fwrite(writer->append, sizeof(char), writer->size_appd, writer->file);
  if (size_push != writer->size_appd) {
    *state |= (1 << ERROR); *error |= (1 << FOERR);
  }//Failed to append data to file.

  if (writer->file) fclose(writer->file);
  return;
}

void write_driver(write_t *writer, uint16_t *state, uint16_t *error) {

  System_Message("Initiates database append.");

  database_trim(writer, state, error);
  database_open(writer, state, error);
  database_push(writer, state, error);

  return;
}