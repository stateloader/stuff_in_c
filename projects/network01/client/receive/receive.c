/*-------------------------------------------------------------------------------------------RECEIVE
Received data being crunched through logical path determend by original request-type (push/pull).
--------------------------------------------------------------------------------------------------*/
#include "../connect/connect.h"
#include <stdlib.h>
#include "publish.h"
#include "receive.h"

static void receive_checks(recv_t *receive) {

	if (receive->package[receive->size_pack - 1] != '\0')
	  Termination_Message("receive_driver", "received package not terminated.");
	  
  if (receive->size_pack < POFFS)
	  Termination_Message("receive_driver", "received package smaller than allowed minimum size.");
	
	receive->protocol[TINDX] = receive->package[receive->size_pack - 4];
  receive->protocol[PINDX] = receive->package[receive->size_pack - 3];
  receive->protocol[CINDX] = receive->package[receive->size_pack - 2];
  
  if (!(receive->protocol[TINDX] & (1 << MSBIT)))
		Termination_Message("receive_driver", "Table bit not set in recieved protocol.");
		
  if (!(receive->protocol[PINDX] & (1 << MSBIT)))
		Termination_Message("receive_driver", "Performance bit not set in recieved protocol.");
		
  if (!(receive->protocol[CINDX] & (1 << MSBIT)))
		Termination_Message("receive_driver", "Check bit not set in received protocol.");
	
	return;
}

static void receive_driver_push(recv_t *receive)  {
/*If data received from a request is of type 'push', only the 'protocol' + terminator is sent back
 *by the server to print a "push-validation"-message.*/

  switch(receive->protocol[TINDX]) {
  case 0x81:
    System_Message("your message was successfully delivered.");
  break;
  case 0x82:
    System_Message("you successfully interacted with the device.");
  break;
  default:
  	Termination_Message("receive_push_request", "default reached in switch-statement.");
  return;
  }
}

static void table_size_fetcher(recv_t *receive, size_t entry_const) {
/*Fetching number of rows in current 'package' by dividing all delims found with the 'entry_const'
 *attached to every row/entry/model. Checks nothing gone south in the process by "modding" the
 *'delim_count' with 'size_rows'.*/
 
  size_t delm_count = 0;
  
  for (size_t i = 0; i < receive->size_pack; i++)
    delm_count += (receive->package[i] == DELIM) ? 1 : 0;
  receive->size_rows = (delm_count / entry_const);
  
  if (delm_count % receive->size_rows != 0)
  	Termination_Message("receive_pull_request", "default reached in switch-statement.");
}

static void receive_driver_pull(recv_t *receive) {
/*If data received from a request is of type 'pull', an entire database (for the moment) being
 *organised into "tables" and published.*/ 

  receive->size_pack -= POFFS;
  
  switch(receive->protocol[TINDX]) {
  case 0x81:
    table_size_fetcher(receive, DMESG); 
    receive->table_mesg = table_mesg_create(receive->package, receive->size_pack, receive->size_rows);
  break;
  case 0x82:
  	table_size_fetcher(receive, DDVCE); 
    receive->table_dvce = table_dvce_create(receive->package, receive->size_pack, receive->size_rows);
  break;
  default:
    Termination_Message("receive_pull_request", "default reached in switch-statement.");
  }
  publish_driver(receive);
  return;
}

void receive_driver(recv_t *receive) {
/*Assigns received data to members of struct-variable 'receive'.*/
 
  receive->size_pack = recv(receive->sock_desc, receive->package, RBUFF, 0);
  receive_checks(receive);
  
  System_Message("response successfully received.");
  
  if (receive->protocol[CINDX] & (1 << PPREQ))
    receive_driver_push(receive);
  else
    receive_driver_pull(receive);
  return;
}

