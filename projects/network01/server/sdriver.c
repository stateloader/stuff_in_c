/*------------------------------------------------------------------------------------SERVER DRIVER
Guess the client's socket-descriptor is the only arg this driver really needs. However, current
structure is in place due to some theading ideas I've down the road.

Various receive-and response-logic taking place inside their "drivers". struct-variable 'receive'
stores received data among its memebers while this data being relayed by the members in 'response'.
-------------------------------------------------------------------------------------------------*/

#include "connect/connect.h"
#include "receive/receive.h"
#include "response/response.h"
#include "jackIO/cstrings.h"
#include "sdriver.h"

void server_driver(driver_t *driver) {
/*'server_driver' doing its thing.*/ 

  recv_t receive  = {.client_sock = driver->server.client_sock_desc};  
	receive_driver(&receive);
		
	resp_t response = {
	  .client_sock = driver->server.client_sock_desc,.protocol = receive.protocol,
	  .size_recv = receive.size_pack,.received = receive.package
	};
	response_driver(&response);
  return;
}
