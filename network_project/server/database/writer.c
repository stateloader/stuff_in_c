#include "writer.h"

static data_item data_items[] = {
//custom datatype for mapping specific data given (...) [vilken model, därmed databas, ärendet rör etc].
  {MCLNT, PCLNT},
  {MSMPL, PSMPL},
  {MMSGE, PMSGE},
};

uint8_t database_writer(uint8_t request, write_t *writer) {
  return SUCC;
}