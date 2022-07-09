#ifndef BITENGINE_H_
#define BITENGINE_H_

#include "../system/configs.h"

#define MODES 0 // mode set bit
#define MODEC 1 // mode clear bit
#define MODET 2 // mode Toggle bit

typedef struct WiseItem {
  const char *name_byte;
  const char *name_flag;
  const uint8_t flag;
} wise_item;

#define PrintInit(bstr) printf("\t|%s| init : ", bstr);
#define PrintMode(fstr, mstr) printf("\t|%s| was %s\n", fstr, mstr);
#define PrintDone(bstr) printf("\t|%s| done : ", bstr);

void bitwise_operation(uint8_t *byte, int32_t mode, uint8_t flag, wise_item *item);

#endif