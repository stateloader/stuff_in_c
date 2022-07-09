/*-------------------------------------------------------------------------------------------------------------------WRITER
Any request from client where pushing/writing/inserting anything to the server ends up here.                                                                                      
/------------------------------------------------------------------------------------------------------------------------*/

#include "writer.h"

static void database_trim(write_t *writer, uint16_t *state, uint16_t *error) {
/*Removes the PROTOCOL (rather trims down the package-size for not including it). Not desired in the database.*/

  writer->size_appd -= POFFS;
  if (writer->append[writer->size_appd - 1] != DELIM) {
    *state |= (1 << ERROR); *error |= (1 << DDERR);
  }
  return;
}

typedef struct WriteItem {
  const uint8_t flag;
  const char *filepath;
} write_item;

static write_item write_items[] = {
  {TMESG, "response/database/mesg.dat"},
  {TDVCE, "response/database/dvce.dat"}
//{FUTURE, "stuff"},
};

static void database_open(write_t *writer, uint16_t *state, uint16_t *error) {
/*For now just two items why this loop isn't really needed but it's in place for scaling when (if) more stuff to handle
 *is in place*/

  if (*state & (1 << ERROR)) return;

  for (size_t i = 0; i < ARRAY_SIZE(write_items); i++) {
    if (writer->protocol[TBIDX] & (1 << write_items[i].flag))
      writer->file = fopen(write_items[i].filepath, "a");

  } if (writer->file == NULL) {
    *state |= (1 << ERROR); *error |= (1 << FOERR);
  }
  return;
}

static void database_push(write_t *writer, uint16_t *state, uint16_t *error)  {
/*Writing (appending) to database*/

  System_Message("Appending to database.");

  if (*state & (1 << ERROR)) return;

  size_t size_push = fwrite(writer->append, sizeof(char), writer->size_appd, writer->file);
  if (size_push != writer->size_appd) {
    *state |= (1 << ERROR); *error |= (1 << FOERR);
  }
  fclose(writer->file);
  return;
}

void write_driver(write_t *writer, uint16_t *state, uint16_t *error) {

  database_trim(writer, state, error);
  database_open(writer, state, error);
  database_push(writer, state, error);

  return;
}