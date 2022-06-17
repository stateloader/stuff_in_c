/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                    WRITER
--------------------------------------------------------------------------------------------------------------------------
info fasda
------------------------------------------------------------------------------------------------------------------------*/
#include "writer.h"

static int8_t write_fileop(write_t *writer) {
  
  writer->file = fopen(writer->witem.filepath, "a");
  return write_fileop_checker(writer);
}

static int8_t write_append(write_t *writer) {

  int32_t size_append = fwrite(writer->witem.package, sizeof(char), writer->witem.size_package, writer->file);
  if (writer->file) fclose(writer->file);
  return write_append_checker(writer->witem.size_package, size_append);
}

int8_t write_driver(write_t *writer) {
  System_Message("inside write_driver");

  if (write_fileop(writer))
    return FAIL;
  else
    return write_append(writer);
}