/*------------------------------------------------------------------------------------SERVER DRIVER
Theading in the pipe, for now the server dealing with one session at the time.

Various receive-and response-logic taking place inside the "drivers". Struct-variable 'receive'
stores received data among its members and (if stuff went well) forwards it to 'response'.
-------------------------------------------------------------------------------------------------*/

#include "connect/connect.h"
#include "receive/receive.h"
#include "response/response.h"
#include "jackIO/cstrings.h"
#include "sdriver.h"

void server_driver(driver_t *driver) {
/*'server_driver' doing its thing.*/ 

  recv_t receive  = {.client_sock = driver->server.client_sock_desc};
	receive_driver(&receive, &driver->status);
	
  resp_t response = {
	  .client_sock = driver->server.client_sock_desc,
	  .protocol = receive.protocol,.size_recv = receive.size_pack,.received = receive.package
	};
	response_driver(&response, &driver->status);	
  return;
}
