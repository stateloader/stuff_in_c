/*------------------------------------------------------------------------------------SERVER DRIVER

-------------------------------------------------------------------------------------------------*/
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

static void database_trim(write_t *writer) {
/*Removes the PROTOCOL, or, rather trims it down for not including the package-data (isn't desired in the database.*/

  writer->size_appd -= POFFS;
  if (writer->append[writer->size_appd - 1] != DELIM) {
    System_Message("creating response.");
  }
  return;
}

static void database_open(write_t *writer) {
 
  System_Message("opens the file.");

  for (size_t i = 0; i < ARRAY_SIZE(write_items); i++) {
    if (writer->protocol[TINDX] & (1 << write_items[i].flag))
      writer->file = fopen(write_items[i].filepath, "a");
  } if (writer->file == NULL) {
    System_Message("creating response.");
  }

  return;
}

static void database_push(write_t *writer)  {
/*Writing (appending) to database.*/

  size_t size_push = fwrite(writer->append, sizeof(char), writer->size_appd, writer->file);
  if (size_push != writer->size_appd) {
    System_Message("creating response.");
  }

  if (writer->file) fclose(writer->file);
  
  return;
}

void write_driver(write_t *writer) {

  database_trim(writer);
  database_open(writer);
  database_push(writer);

  return;
}
