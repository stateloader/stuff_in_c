/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                    WRITER
--------------------------------------------------------------------------------------------------------------------------
info fasda
------------------------------------------------------------------------------------------------------------------------*/
#include "writer.h"

int8_t phase_fileappd(write_t *writer) {

  writer->file = fopen(writer->item->path, "a");
  if (!fileopen_check(writer->file))
    return FAIL;

  writer->size_appd -= 2;

  int32_t size_writ = fwrite(writer->appd, sizeof(char), writer->size_appd, writer->file);
  if (!fileappd_check(size_writ, writer->size_appd, writer->file))
    return FAIL;

  return SUCC;
}

int8_t write_driver(write_t *writer) {
  System_Message("inside write_driver");
  return phase_fileappd(writer);
}