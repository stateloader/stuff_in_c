/*------------------------------------------------------------------------------------------------------------SERVER DRIVER
Main driver. Runs until something goes (very) south.                                                                                             
/------------------------------------------------------------------------------------------------------------------------*/
#include "connect/connection.h"
#include "receive/receiver.h"
#include "response/responder.h"
#include "system/error.h"
#include "system/configs.h"
#include "system/cstrings.h"
#include "sdriver.h"

static void state_receive(recv_t *receive, dver_t *driver) {
/*Receive state, core logic runs inside the receive-driver. See RECEIVE MODULE.*/

  if (driver->status & (1 << ERROR)) return;
//If error bit is set, fall through.
  receive_driver(receive, &driver->status, &driver->error);

  return;
}

static void state_courier(resp_t *response, recv_t *receive, dver_t *driver) {
/*After a package has (successfully) been received, this state is about copy received content over to the responder while
 *some checks beeing done. A "middle-hand" of some sort. In earlier interpretations I just pointed at the received data in
 *later states. It worked, but tended to behave unpredictable sometimes for some reason why I settled on this solution.*/

  if (driver->status & (1 << ERROR)) return;
//If error bit is set, fall through.

  response->protocol[TBIDX] = receive->protocol[TBIDX];
  response->protocol[ABIDX] = receive->protocol[ABIDX];
  response->protocol[EBIDX] = receive->protocol[EBIDX];

  response->size_recv = string_copy(response->received, receive->package, SBUFF);
  if (response->size_recv != receive->size_pack) {
    driver->status |= (ERROR); driver->error |= (1 << PCERR);
  }
  return;
}

static void state_respond(resp_t *response, dver_t *driver) {
/*Response state, core logic being ran inside the receive-driver. See RESPONSE MODULE.*/

  if (driver->status & (1 << ERROR)) return; 
//If error bit is set, fall through.
  response_driver(response, &driver->status, &driver->error);

  return;
}

static void state_flusher(resp_t *response, recv_t *receive, dver_t *driver) {

  buffer_flush(response->received, SBUFF);
  buffer_flush(response->response, RBUFF);
  buffer_flush(receive->package, SBUFF);

  error_driver(driver->status, driver->error);
  close(driver->server.client_sock_desc);
}

void server_driver(dver_t *driver) {

  socket_listen(&driver->server, &driver->status, &driver->error);
  socket_accept(&driver->server, &driver->status, &driver->error);

  recv_t receive =  {.client_sock_desc = driver->server.client_sock_desc};
  resp_t response = {.client_sock_desc = driver->server.client_sock_desc};
  
  state_receive(&receive, driver);
  state_courier(&response, &receive, driver);
  state_respond(&response, driver);
  state_flusher(&response, &receive, driver);
}