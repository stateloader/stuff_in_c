/*------------------------------------------------------------------------------------------------------------------------
                                                                                                             WRITER MODULE
--------------------------------------------------------------------------------------------------------------------------
info fasda
------------------------------------------------------------------------------------------------------------------------*/

#include "nstrings.h"
#include "writer.h"

static data_item data_items[] = {
  {MCLNT, PCLNT},
  {MSMPL, PSMPL},
  {MMSGE, PMSGE},
};

static void decode_request(uint8_t request, write_t *writer) {

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

  writer->append_size = fwrite(writer->package, sizeof(char), writer->package_size, writer->file);
  uint8_t result = (writer->append_size > 0) ? SUCC : FAIL;
  if (writer->file) fclose(writer->file);
  return result;
}

uint8_t database_writer(uint8_t request, write_t *writer) {

  decode_request(request, writer);

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
//printf("package inside writer: %s\n", writer->package);
//printf("sizepac inside writer: %ld\n", writer->package_size);