/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                   CONFIGS
--------------------------------------------------------------------------------------------------------------------------
Info info info
------------------------------------------------------------------------------------------------------------------------*/
#include "configs.h"

int8_t protocol_append(char *package, int32_t size_pack, uint8_t *protocol) {

  protocol[TINDX] = package[size_pack - 4];
  protocol[EINDX] = package[size_pack - 3];
  protocol[FINDX] = package[size_pack - 2];

  if (!check_term(package, size_pack)) {
    Message_Info("--error-- package not nullterminated");
    return FAIL;
  }
  return SUCC;
}