#include "dbconfigs.h"
#include "filedriver.h"

int main(void) {
  filed_t driver = {.rows = 0};
  driver.bill = READ_CLIENT_ROUTINE;
  uint8_t majs = file_driver(&driver);
  free_driver(&driver);
  return 0;
}