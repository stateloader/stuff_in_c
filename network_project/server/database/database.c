#include "database.h"
#include "reader.h"
#include "writer.h"

static uint8_t request = 0x00;

/*-----------------------------------------------------------------------------------------------------------------------
|    7    |    6    |    5    |    4    |    3    |     2    |     1     |     0     |  position
|   R/W   |    -    |    -    |    -    |    -    |   MMSGE  |   MSMPL   |   MCLNT   |  variable
-----------------------------------------------------------------------------------------------------------------------*/

static uint8_t decode_route(uint8_t request) {

  uint8_t mask = request, route = 0;
  route = (mask & (1 << 7)) ? WINIT: RINIT;

  return route;
}

int main(void) {

  request |= (0 << 7) | (1 << MCLNT);

  uint8_t result = 0;
  read_t reader = {.rows = 0};

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