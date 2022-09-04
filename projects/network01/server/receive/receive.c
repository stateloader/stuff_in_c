/*-----------------------------------------------------------------------------------RECEIVE DRIVER
Receiving data from client before doing some checks making sure nothing gone south.
-------------------------------------------------------------------------------------------------*/

#include <sys/socket.h>
#include "receive.h"

static void receive_checks(recv_t *receive) {

	if (receive->package[receive->size_pack - 1] != '\0')
	  Termination_Message("request_driver", "request package not terminated.");

  if (receive->size_pack < POFFS)
	  Warning_Message("request_driver", "request package smaller than allowed minimum size.");

  receive->protocol[TINDX] = receive->package[receive->size_pack - 4];
  receive->protocol[PINDX] = receive->package[receive->size_pack - 3];
  receive->protocol[CINDX] = receive->package[receive->size_pack - 2];

	if (receive->protocol[TINDX] == 0x80)
		Warning_Message("request_driver", "request hasn't any Table set.");
  
  if (!(receive->protocol[TINDX] & (1 << MSBIT)))
		Warning_Message("request_driver", "MSBIT not set in protocol Table byte.");
		
  if (!(receive->protocol[PINDX] & (1 << MSBIT)))
		Warning_Message("request_driver", "MSBIT not set in protocol Performance byte.");
		
  if (!(receive->protocol[CINDX] & (1 << MSBIT)))
		Warning_Message("request_driver", "MSBIT not set in protocol Check Byte.");
	
	return;
}

void receive_driver(recv_t *receive) {

  receive->size_pack = recv(receive->client_sock, receive->package, SBUFF, 0);
  receive_checks(receive);
  
  return;
}
