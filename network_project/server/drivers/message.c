#include "message.h"


static int8_t dispatch(server_t *server) {
  return (server->protocol[EINDX] & (1 << RWBIT)) ? 1 : 0;
}

void message_driver(server_t *server) {
  System_Message("inside message driver");
  /*
  switch(dispatch(server)) {
  case 0:

    
    
  }
  */
}