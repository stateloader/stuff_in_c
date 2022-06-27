#include "configs.h"

void datetime_append(char *datetime) {
  strncat(datetime, __DATE__, TBUFF);
  strncat(datetime, " ", TBUFF);
  strncat(datetime, __TIME__, TBUFF);
  datetime[TBUFF - 1] = DELIM;
}

void protocol_append(char *package, int32_t size_pack, uint8_t *protocol) {

  package[size_pack - 4] = protocol[TINDX];
  package[size_pack - 3] = protocol[EINDX];
  package[size_pack - 2] = protocol[FINDX];
  package[size_pack - 1] = '\0';
}
