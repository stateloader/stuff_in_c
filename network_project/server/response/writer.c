#include "writer.h"

static void package_scale(write_t *writer, uint16_t *state, uint16_t *error) {

  writer->size_pack -= POFFS;
  if (writer->package[writer->size_pack - 1] != DELIM) {
    *state |= (1 << ERROR); *error |= (1 << WSERR);
  }
  return;
}

typedef struct WriteItem {
  const uint8_t flag;
  const char *filepath;
} write_item;

static write_item write_items[] = {
  {TMESG, "response/database/mesg.dat"},
  {TDVCE, "response/database/dvce.dat"},
};

static void database_open(write_t *writer, uint16_t *state, uint16_t *error) {

  if (*state & (0 << ERROR)) return;
  System_Message("Opens file.");

  int8_t match = 0;
  for (size_t i = 0; i < ARRAY_SIZE(write_items); i++) {
    if (writer->protocol[TBIDX] & (1 << write_items[i].flag)) {
      writer->file = fopen(write_items[i].filepath, "a");
      match++; break;
    }
  } if (match == 0) {
    if (writer->file) fclose(writer->file);
    *state |= (1 << ERROR); *error |= (1 << ITERR);
  } if (writer->file == NULL) {
    if (writer->file) fclose(writer->file);
    *state |= (1 << ERROR); *error |= (1 << FOERR);
  }
  return;
}

static void database_append(write_t *writer, uint16_t *state, uint16_t *error)  {
  
  if (*state & (0 << ERROR)) return;
  System_Message("Appending to database.");


  size_t size_write = fwrite(writer->package, sizeof(char), writer->size_pack, writer->file);
  if (size_write != writer->size_pack) {
    *state |= (1 << ERROR); *error |= (1 << FOERR);
  }
  fclose(writer->file);
  return;
}

void write_driver(write_t *writer, uint16_t *state, uint16_t *error) {

  package_scale(writer, state, error);
  database_open(writer, state, error);
  database_append(writer, state, error);

  return;
}