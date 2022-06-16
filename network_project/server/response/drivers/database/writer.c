/*------------------------------------------------------------------------------------------------------------------------
                                                                                                             WRITER MODULE
--------------------------------------------------------------------------------------------------------------------------
info fasda
------------------------------------------------------------------------------------------------------------------------*/
#include "writer.h"

int8_t write_driver(write_t *write) {
 return SUCC;
}
/*
static data_item data_items[] = {
  {MCLNT, PCLNT},
  {MSMPL, PSMPL},
  {MMSGE, PMSGE},
  {MDVCE, PDVCE},
};

static void decode_request(write_t *writer) {

  uint8_t check_bit = 0;
  uint8_t reqmask = writer->request;
  
  while (check_bit < 7) {
    if (reqmask & 0x01)
      writer->item = data_items[check_bit];
    check_bit++;
    reqmask = reqmask >> 1;
  }
}

static uint8_t open_file(write_t *writer) {

  uint8_t result = (writer->file = fopen(writer->item.file_path, "a")) != NULL ? SUCC : FAIL;
  return result;
}

static uint8_t append_file(write_t *writer) {

  writer->append_size = fwrite(writer->package, sizeof(char), writer->package_size, writer->file);
  uint8_t result = (writer->append_size > 0) ? SUCC : FAIL;
  if (writer->file) fclose(writer->file);
  return result;
}

uint8_t database_writer(write_t *writer) {

  decode_request(writer);

  if (open_file(writer)) {
    printf("sucess open\n");
  } else {
    printf("filed open\n");
    return FAIL;
  }
  if (append_file(writer)) {
    printf("success append\n");
    return SUCC;
  } else {
    printf("failed append\n");
    return FAIL;
  }
}
*/