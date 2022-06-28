/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                   CONFIGS
--------------------------------------------------------------------------------------------------------------------------
Info info info
------------------------------------------------------------------------------------------------------------------------*/
#include "configs.h"

int8_t datetime_append(char *datetime) {

  strncat(datetime, __DATE__, TBUFF);
  strncat(datetime, " ", TBUFF);
  strncat(datetime, __TIME__, TBUFF);
  datetime[TBUFF - 1] = DELIM;

  if (!check_delm(datetime, TBUFF)) {
    Message_Info("datetime missing delimiter.");
    return FAIL;
  }
  return SUCC;
}

int8_t protocol_append(char *package, int32_t size_pack, uint8_t *protocol) {

  package[size_pack - 4] = protocol[TINDX];
  package[size_pack - 3] = protocol[AINDX];
  package[size_pack - 2] = protocol[FINDX];
  package[size_pack - 1] = '\0';

  if (!check_term(package, size_pack)) {
    Message_Info("package not nullterminated.");
    return FAIL;
  }
  return SUCC;
}
