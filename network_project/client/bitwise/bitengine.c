/*----------------------------------------------------------------------------------------------------------------BITENGINE
Put on ice for the moment.                                                                      
-------------------------------------------------------------------------------------------------------------------------*/
#include "bitengine.h"

static void print_init(uint8_t *byte, uint8_t flag, wise_item *item) {
  System_Message("Bitoperation\n");
  PrintInit(item[flag].name_byte);
  PrintByte(*byte);
}

static void print_done(uint8_t *byte, uint8_t flag, wise_item *item) {
  PrintDone(item[flag].name_byte);
  PrintByte(*byte);
  printf("\n");
}

void bitwise_operation(uint8_t *byte, int32_t mode, uint8_t flag, wise_item *item) {
/*Engine of some sort dealing with bitoperations.*/

  print_init(byte, flag, item);
  switch(mode) {
  case MODES:
    *byte |= (1 << item[flag].flag);
    PrintMode(item[item->flag].name_flag, "set");
  break;
  case MODEC:
    *byte &= ~(1 << item[flag].flag);
    PrintMode(item[item->flag].name_flag, "cleared");
  break;
  case MODET:
    *byte ^= (1 << item[flag].flag);
    PrintMode(item[item->flag].name_flag, "toggled");
  break;
  }
  print_done(byte, flag, item);
}