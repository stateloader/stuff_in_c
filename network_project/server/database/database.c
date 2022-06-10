#include "database.h"
#include "reader.h"

static uint8_t request = 0x00;

/*-----------------------------------------------------------------------------------------------------------------------
                                                                                                               ROUTE BYTE
-------------------------------------------------------------------------------------------------------------------------
|    7    |    6    |    5    |    4    |    3    |     2    |     1     |     0     |  position
|   R/W   |    -    |    -    |    -    |    -    |   MMSGE  |   MSMPL   |   MCLNT   |  variable
-------------------------------------------------------------------------------------------------------------------------

------------------------------------------------------------------------------------------------------------------------*/

static uint8_t decode_route(uint8_t request) {
//setups a "route-stack" (read or write, which table etc.) by parsing a route-byte sent from the response-module.
  uint8_t mask = request, route = 0;
  route = (mask & (1 << 7)) ? WINIT: RINIT;

  return route;
}

int main(void) {

  request |= (0 << 7) | (1 << MCLNT);

  uint8_t result = 0;
  read_t reader = {.model = 0x00};

  switch(decode_route(request)) {
  
  case RINIT:
    result = database_reader(request, &reader);
    printf("test result: %d\n", result);
    break;
  
  case WINIT:
    printf("WINIT RUN.\n");
    break;
  }

  reader_free(&reader);
  return 0;
}