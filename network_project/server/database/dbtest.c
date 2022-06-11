#include "../serverutils/serror.h"
#include "../serverutils/sstrings.h"
#include "dbconfig.h"
#include "database.h"
#include "reader.h"
#include "writer.h"

/*---------------------------------------------------------------------------------------------------------BYTE: "REQUEST"
bit                |    7    |    6    |    5    |    4    |    3    |     2    |     1     |     0     |
constant           |  RWBIT  |  UCRTE  |    -    |    -    |  MTHNG  |   MMSGE  |   MSMPL   |   MCLNT   |
------------------------------------------------------------------------------------------------------------------------*/

int main(void) {


  read_t reader = {0};
  write_t writer = {0};

  uint8_t result = 0, request = 0x00;

  const char *package = "jackepken|pasord|";

  request |= (WINIT << RWBIT) | (1 << MCLNT);    // read
  result = database_driver(&reader, &writer, request, package);

  Integer_Info_Message(result, "result after r/w routine");

  reader_free(&reader);
  return 0;
}