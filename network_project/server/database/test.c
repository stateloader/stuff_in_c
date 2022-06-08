#include "dbconfigs.h"
#include "filedriver.h"

int main(void) {
  filed_t driver = {.routine = READ_ROUTINE,.model = CLIENT};
  uint8_t result = file_driver(&driver);
  printf("result : %d\n", result);
  free_driver(&driver);
  return 0;
}