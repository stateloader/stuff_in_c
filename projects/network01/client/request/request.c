/*-------------------------------------------------------------------------------------------REQUEST
Data being stored among members in struct-variable 'request' and formatted into a package before
sending it to the server. This package is assembled within various "drivers", a logical path decided 
by the bit-configuration(s) in the 'protocol'.
--------------------------------------------------------------------------------------------------*/

#include <string.h>
#include <stdlib.h>
#include "../connect/connect.h"
#include "../jackIO/cstrings.h"
#include "device.h"
#include "message.h"
#include "request.h"

static void request_checks(reqt_t *request) {
//*Some checks before Bon voyage.*/

	if (request->protocol[TINDX] == 0x80)
		Termination_Message("request_driver", "request hasn't any Table set.");

	if (request->package[request->size_pack - 1] != '\0')
	  Termination_Message("request_driver", "request package not terminated.");
	  
  if (request->size_pack < POFFS)
	  Termination_Message("request_driver", "request package smaller than allowed minimum size.");
  
  if (!(request->package[request->size_pack - 4] & (1 << MSBIT)))
		Termination_Message("request_driver", "Table byte not set in request package.");
		
  if (!(request->package[request->size_pack - 3] & (1 << MSBIT)))
		Termination_Message("request_driver", "Performance byte not set in request package.");
		
  if (!(request->package[request->size_pack - 2] & (1 << MSBIT)))
		Termination_Message("request_driver", "Check byte not set in request protocol.");
	
	return;
}

//At the moment there's just two tables, message and device, why this approach is a bit cumbersome
//but it's in place to make it more scalable as (maybe) more 'tables' being created down the road.

typedef void (*reqt_func)(reqt_t *request);

typedef struct RequestItem {
  const uint8_t table;
  reqt_func func;
} reqt_item;

static reqt_item table_items[] = {
  {TMESG, message_driver}, {TDVCE, device_driver}
};

void request_driver(reqt_t *request) {
/*Iterates through 'reqt_items', list of struct-variables of type 'reqt_item'. If the Table-Byte of
 *the protocol (TINDX) matches member 'table', corresponding function-pointer in the same item will
 *be dereferenced.*/
 
  for (size_t i = 0; i < ARRAY_SIZE(table_items); i++) {
    if (request->protocol[TINDX] & (1 << table_items[i].table))
      table_items[i].func(request);
  }
  request_checks(request);
  size_t size_send = send(request->sock_desc, request->package, request->size_pack, 0);
    
  if (size_send < POFFS)
    Termination_Message("request_driver", "something went south while sending segment.");
  System_Message("sending request to server.");
  return;
}
