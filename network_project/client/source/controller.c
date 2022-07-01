/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                   CONFIGS
--------------------------------------------------------------------------------------------------------------------------
Info info info
------------------------------------------------------------------------------------------------------------------------*/
#include "controller.h"

int8_t datetime_append(char *datetime) {

  strncat(datetime, __DATE__, TBUFF);
  strncat(datetime, " ", TBUFF);
  strncat(datetime, __TIME__, TBUFF);
  datetime[TBUFF - 1] = DELIM;

  if (!check_delm(datetime, TBUFF)) {
    System_Message("datetime missing delimiter.");
    return FAIL;
  }
  return SUCC;
}

static int8_t protocol_append_checks(char *package, int32_t size_pack) {

  for (int8_t i = 0, j = 4; i < 3; i++, j--) {
    if (package[j] & (0 << UNBIT)) {
      System_Message("error: protocol bytes isn't in correct format.");
      return FAIL;
    }
   } if (!check_term(package, size_pack)) {
    System_Message("package not nullterminated.");
    return FAIL;
   }
   return SUCC;
}

int8_t protocol_append(char *package, int32_t size_pack, uint8_t *protocol) {

  package[size_pack - 4] = protocol[TBYTE];
  package[size_pack - 3] = protocol[ABYTE];
  package[size_pack - 2] = protocol[SBYTE];
  package[size_pack - 1] = '\0';

  return protocol_append_checks(package, size_pack);
}
