/*----------------------------------------------------------------------------------RESPONSE DRIVER

-------------------------------------------------------------------------------------------------*/

#include <sys/socket.h>
#include "../jackIO/cstrings.h"
#include "reader.h"
#include "writer.h"
#include "response.h"

static void protocol_attach(resp_t *response) {
/*Adds 'POFFS' (4 bytes) to the size of the response-string making room for 'protocol'.*/

	response->size_resp += POFFS;

  response->response[response->size_resp - 4] = response->protocol[TINDX];
  response->response[response->size_resp - 3] = response->protocol[PINDX];
  response->response[response->size_resp - 2] = response->protocol[CINDX];
  response->response[response->size_resp - 1] = '\0';

  return;
}

static void database_pull(resp_t *response) {
/*Requested table will be fetched from given database and copied to the response-string.*/

  read_t reader = {.size_pull = 0};
  reader.protocol = response->protocol;

  read_driver(&reader);
  response->size_resp = string_copy(RBUFF, response->response, reader.read) - 1;
  
  return;
}

static void database_push(resp_t *response) {
/*Database will be appended with data sent from the client.*/

  write_t writer = {.size_push = response->size_recv};
  writer.protocol = response->protocol;
  writer.append = response->received;

  write_driver(&writer);
  
  return;
}

void response_driver(resp_t *response, uint8_t *status) {
/*Bit set in 'status' going to decide which path being taken in the switch-statement.*/

  switch(*status) {
  case 0x01: // SCONN, nothing out of the ordinary.
		if (response->protocol[CINDX] & (1 << PPREQ))
		  database_push(response);
		else
		  database_pull(response);
		protocol_attach(response);
		System_Message("sending response [success] to client.");
		send(response->client_sock, response->response, response->size_resp, 0);
  break;
  
  case 0x03: // client request corrupted somehow, 'CFAIL' set in the response's 'Check-Byte'.
    response->protocol[CINDX] |= (1 << CFAIL);
    protocol_attach(response);
    System_Message("sending response [error client side] to client.");
    send(response->client_sock, response->response, response->size_resp, 0);
    
    *status &= ~(1 << CWARN); *status |= (1 << SCONN);

  break;
  
  case 0x07: // only received non terminated packages terminates (atm), hence 'CFAIL'.
    response->protocol[CINDX] |= (1 << CFAIL);
    protocol_attach(response);
    System_Message("sending response [error client side] to client.");
    send(response->client_sock, response->response, response->size_resp, 0);
  break;
  
  default:		// reached default, some serious server-error.
    response->protocol[CINDX] |= (1 << SFAIL);
    protocol_attach(response);
    System_Message("sending response [error server side] to client.");
    send(response->client_sock, response->response, response->size_resp, 0);
    
    *status &= ~(1 << SCONN); *status |= (1 << SFAIL);
  }
  close(response->client_sock);
  
  return;
}
