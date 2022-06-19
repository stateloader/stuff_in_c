/*------------------------------------------------------------------------------------------------------------------------
                                                                                                             READER
--------------------------------------------------------------------------------------------------------------------------
info fasda
------------------------------------------------------------------------------------------------------------------------*/
#include "sstring.h"
#include "reader.h"

int8_t fileread(read_t *reader) {
  System_Message("Inside fileread");
  System_Message(reader->item->path);
  /*
  reader->file = fopen(reader->item->path, "r");
  //if (!fileopen_check(reader->file))
   // return FAIL;

  reader->size_file = fread(reader->file_data, sizeof(char), FBUFF - 1, reader->file);
  if (!fileread_check(reader->size_file, reader->file))
    return FAIL;
  */
  return SUCC;
}
int8_t read_driver(read_t *reader) {
  System_Message("Inside read_driver");
  return fileread(reader);
}