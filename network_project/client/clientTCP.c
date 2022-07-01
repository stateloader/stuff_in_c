/*------------------------------------------------------------------------------------------------------------------------
                                                                                                               CLIENT MAIN
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/
#include "source/controller.h"
#include "source/client.h"
#include "source/connect.h"
#include "source/session.h"

int main(void) {

  int8_t result = 0;
  
  client_t client = {0};

  result = connect_create(&client, "127.0.0.1", 90190);
  if (result < SUCC) exit(EXIT_FAILURE);

  result = session_driver(&client);
  if (result < SUCC) exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);
}