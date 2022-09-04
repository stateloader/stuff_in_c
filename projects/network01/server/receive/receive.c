/*-----------------------------------------------------------------------------------RECEIVE DRIVER
Receive logic.
-------------------------------------------------------------------------------------------------*/

#include <sys/socket.h>
#include "receive.h"

static uint8_t receive_checks(recv_t *receive) {
/*Received packages being checked for errors. The only error resulting in server-termination atm is
 *not nullterminated packages which will set 'STERM' (Server Termination) bit to 'status' while
 *Other errors set 'CWARN' (Client Warning).*/
 
	if (receive->package[receive->size_pack - 1] != '\0')
	  return Termination_Message("request_driver", "request package not terminated.");

  if (receive->size_pack < POFFS)
	  return Warning_Message("request_driver", "request package smaller than allowed minimum size.");

  receive->protocol[TINDX] = receive->package[receive->size_pack - 4];
  receive->protocol[PINDX] = receive->package[receive->size_pack - 3];
  receive->protocol[CINDX] = receive->package[receive->size_pack - 2];

	if (receive->protocol[TINDX] == 0x80)
		return Warning_Message("request_driver", "request hasn't any Table set.");
  
  if (!(receive->protocol[TINDX] & (1 << MSBIT)))
		return Warning_Message("request_driver", "MSBIT not set in protocol Table byte.");
		
  if (!(receive->protocol[PINDX] & (1 << MSBIT)))
		return Warning_Message("request_driver", "MSBIT not set in protocol Performance byte.");
		
  if (!(receive->protocol[CINDX] & (1 << MSBIT)))
		return Warning_Message("request_driver", "MSBIT not set in protocol Check Byte.");
	
	return SCONN;
}

void receive_driver(recv_t *receive, uint8_t *status) {
/*Clears SCONN from 'status' (i.e: entire byte is now 0) before receiving package from client.
 *Return-vaue in upcoming 'receive_checks' then (re)set 'status' as either 'STERM', 'CWARN' or
 *'SCONN' (nothing out of the ordinary)*/
 
  *status &= ~(1 << SCONN);
  receive->size_pack = recv(receive->client_sock, receive->package, SBUFF, 0);
  
  *status |= (1 << receive_checks(receive));
  return;
}
