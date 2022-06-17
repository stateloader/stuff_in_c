/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                    WRITER
--------------------------------------------------------------------------------------------------------------------------
info fasda
------------------------------------------------------------------------------------------------------------------------*/
#include "writer.h"

int8_t write_driver(write_t *writer) {
  System_Message("inside write_driver");

  writer->file = fopen(writer->path, "a");
  if (!fileop_checker(writer))
    return FAIL;

  writer->size_appd -= 1;

  int32_t size_fwrite = fwrite(writer->appd, sizeof(char), writer->size_appd, writer->file);
  fclose(writer->file);
  
  return append_checker(size_fwrite, writer),
}