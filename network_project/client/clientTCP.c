#include <stdlib.h>
#include "configs.h"
#include "controller.h"

int main(void) {
  Render_Header("Client", "Client ipsum dolor sit amet, consectetur adipiscing elit");

  cont_t controller = {.state = 0x00};
  controller.state |= (1 << ALIVE);
  while (controller.state & (1 << ALIVE))
    control_driver(&controller);
  exit(EXIT_SUCCESS);
}
