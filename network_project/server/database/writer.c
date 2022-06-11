/*------------------------------------------------------------------------------------------------------------------------
                                                                                                             WRITER MODULE
--------------------------------------------------------------------------------------------------------------------------
info fasda
------------------------------------------------------------------------------------------------------------------------*/
#include "../serverutils/serror.h"
#include "../serverutils/sstrings.h"
#include "writer.h"

static data_item data_items[] = {
  {MCLNT, PCLNT},
  {MSMPL, PSMPL},
  {MMSGE, PMSGE},
};

static void decode_request(write_t *writer, uint8_t request) {

  uint8_t check_bit = 0;
  
  while (check_bit < 7) {
    if (request & 0x01)
      writer->item = data_items[check_bit];
    check_bit++;
    request = request >> 1;
  }
}

static uint8_t write_fetch_file(write_t *writer) {

  uint8_t result = (writer->file = fopen(writer->item.file_path, "a")) != NULL ? SUCC : FAIL;
  return result;
}

static uint8_t write_append_file(write_t *writer) {

  writer->asize = fwrite(writer->package, sizeof(char), writer->psize, writer->file);
  uint8_t result = (writer->asize > 0) ? SUCC : FAIL;
  if (writer->file) fclose(writer->file);
  return result;
}

uint8_t database_writer(write_t *writer, uint8_t request) {

  decode_request(writer, request);

  if (write_fetch_file(writer)) {
    printf("sucess open\n");
  } else {
    printf("filed open\n");
    return FAIL;
  }
  if (write_append_file(writer)) {
    printf("success append\n");
    return SUCC;
  } else {
    printf("failed append\n");
    return FAIL;
  }
}