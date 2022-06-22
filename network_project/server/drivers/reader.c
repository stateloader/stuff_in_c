/*------------------------------------------------------------------------------------------------------------------------
                                                                                                             READER
--------------------------------------------------------------------------------------------------------------------------
info fasda
------------------------------------------------------------------------------------------------------------------------*/
#include "sstring.h"
#include "reader.h"

int8_t fileread(read_t *reader) {
  System_Message("Inside fileread");
  return SUCC;
}
int8_t read_driver(read_t *reader) {
  System_Message("Inside read_driver");
  
  return fileread(reader);
}