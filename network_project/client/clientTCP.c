/*------------------------------------------------------------------------------------------------------------------------
                                                                                                               CLIENT MAIN
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/
#include "source/configs.h"
#include "source/client.h"
#include "source/connect.h"
#include "source/session.h"

int main(void) {

  client_t client = {0};
  connect_driver(&client, "127.0.0.1", 90190);  
  //session_driver(&client);
  
  exit(EXIT_SUCCESS);
}