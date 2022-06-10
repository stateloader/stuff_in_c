#include "database.h"
#include "nstrings.h"
#include "reader.h"
#include "writer.h"


static uint8_t TEST_request = 0x00;
static char *TEST_package = "usisfanbasten|numberowdwd|";

/*-----------------------------------------------------------------------------------------------------------------------
|    7    |    6    |    5    |    4    |    3    |     2    |     1     |     0     |  position
|   R/W   |    -    |    -    |    -    |    -    |   MMSGE  |   MSMPL   |   MCLNT   |  constant
-----------------------------------------------------------------------------------------------------------------------*/

static uint8_t database_copy_package(size_t *size, char *dest, const char *from) {

  int8_t result = string_copy(size, dest, from);

  if (result == VALID)
    return SUCC;
  else if (result == ABORT)
    return FAIL;
  else
    exit(EXIT_FAILURE);
}

static uint8_t database_decode_route(uint8_t TEST_request) {

  uint8_t mask = TEST_request, route = 0;
  route = (mask & (1 << 7)) ? WINIT: RINIT;

  return route;
}

int main(void) {

  TEST_request |= (0 << 7) | (1 << MCLNT);

  uint8_t result = 0;
  read_t reader = {.rows = 0};
  write_t writer = {0};

  switch(database_decode_route(TEST_request)) {
  
  case RINIT:
    result = database_reader(TEST_request, &reader);
    printf("package inside writer: %s\n", reader.table_client[0].username);
    printf("test reader result: %d\n", result);
    break;
  
  case WINIT:
    result = (database_copy_package(&writer.package_size, writer.package, TEST_package)) ? database_writer(TEST_request, &writer) : FAIL;
    printf("test writer result: %d\n", result);
    break;
  }

  reader_free(&reader);
  return 0;
}