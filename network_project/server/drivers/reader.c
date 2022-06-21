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
  return SUCC;
}
int8_t read_driver(read_t *reader) {
  System_Message("Inside read_driver");
  return fileread(reader);
}