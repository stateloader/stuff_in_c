#include "database.h"
#include "filedriver.h"

static uint8_t route = 0x00;

/*-----------------------------------------------------------------------------------------------------------------------
                                                                                                               ROUTE BYTE
-------------------------------------------------------------------------------------------------------------------------
|    7    |    6    |    5    |    4    |    3    |     2    |     1     |     0     |  position
|   R/W   |    -    |    -    |    -    |    -    |   MMSGE  |   MSMPL   |   MCLNT   |  variable
-------------------------------------------------------------------------------------------------------------------------

------------------------------------------------------------------------------------------------------------------------*/

table_item table_items[] = {

  {MCLNT, CCLNT, "resources/client.txt"},
  {MSMPL, CSMPL, "resources/sample.txt"},
  {MMSGE, CMSGE, "resources/message.txt"},
};

static void encode_byte(uint8_t request, filed_t *driver) {
  
  uint8_t check_bit = 0;
  while (check_bit < 7) {
    if (request & 0x01)
      driver->item = table_items[check_bit];
    check_bit++;
    request = request >> 1;
  }
  driver->route = (request & (1 << 7) ? WINIT: RINIT);
}


int main(void) {
  uint8_t request = 0;
  request |= (1 << 7) | (1 << MMSGE);
  filed_t driver = {.route = route};
  encode_byte(request, &driver);
  printf("UTANFÖR LOOP: item idx =  %s\n", driver.item.file_path);
  uint8_t result = file_driver(&driver);
  //free_driver(&driver);
  return 0;
}