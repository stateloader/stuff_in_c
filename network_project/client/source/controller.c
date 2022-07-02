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

  if (datetime[TBUFF - 1] != '|') {
    System_Message("datetime missing delimiter.");
    return FAIL;
  }
  return SUCC;
}

int8_t delimiter_check(char *package, int32_t size_pack, int32_t expected) {
  
  int32_t amnt_delim = 0;

  for (int32_t i = 0; i < size_pack; i++)
    amnt_delim += (package[i] == DELIM) ? 1 : 0;
    
  if (amnt_delim != expected) {
    System_Message("corrupted format on package.");
    return FAIL;
  }
  return SUCC;
}

static int8_t protocol_append_checks(char *package, int32_t size_pack) {

  if (package[size_pack - 4] & (0 << UNBIT)) {
    System_Message("TBYTE not unsigned");
    return FAIL;
  }
  if (package[size_pack - 3] & (0 << UNBIT)) {
    System_Message("ABYTE not unsigned");
    return FAIL;
  }
  if (package[size_pack - 2] & (0 << UNBIT)) {
    System_Message("SBYTE not unsigned");
    return FAIL;
  }
  if (package[size_pack - 1] != '\0') {
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

static int8_t protocol_obtain_checks(char *package, int32_t size_pack, uint8_t *protocol) {

  if (package[size_pack - 1] != '\0') {
    System_Message("package not nullterminated.");
    return FAIL;
  }
  if (protocol[TBYTE] & (0 << UNBIT)) {
    System_Message("TBYTE not unsigned");
    return FAIL;
  }
  if (protocol[ABYTE] & (0 << UNBIT)) {
    System_Message("ABYTE not unsigned");
    return FAIL;
  }
  if (protocol[SBYTE] & (0 << UNBIT)) {
    System_Message("SBYTE not unsigned");
    return FAIL;
  }
  System_Message("\tPROTOCOL OK");
  return SUCC;
}

int8_t protocol_obtain(char *package, int32_t size_pack, uint8_t *protocol) {

  protocol[TBYTE] = package[size_pack - 4];
  protocol[ABYTE] = package[size_pack - 3];
  protocol[SBYTE] = package[size_pack - 2];

  return protocol_obtain_checks(package, size_pack, protocol);
}