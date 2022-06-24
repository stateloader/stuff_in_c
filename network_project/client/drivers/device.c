/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                    DEVICE
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/
#include <string.h>
#include "device.h"

static void fetch_datetime(char *datetime) {
  strncat(datetime, __DATE__, TBUFF);
  strncat(datetime, " ", TBUFF);
  strncat(datetime, __TIME__, TBUFF);
  return;
}

void device_driver(rqst_t *request) {
  System_Message("Inside device driver");
}
