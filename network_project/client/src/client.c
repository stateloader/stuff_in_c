/*------------------------------------------------------------------------------------------------------------------------
                                                                                                             CLIENT MODULE
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/

#include "scan.h"
#include "command.h"
#include "client.h"

void print_byte(uint8_t byte) {
  for (uint8_t i = 1 << 7; i > 0; i = i / 2)
    (byte & i) ? printf("1") : printf("0");
  printf("\n");
}

void client_session(cent_t *client) {

	while (1) {
    
    memset(client->response, '\0', MAX_BUFFER);

		client->length = command_driver(client->command, &client->state);
	  printf("length: %ld\n", client->length);

	  if (send(client->conn.socket, client->command, MAX_BUFFER, 0) < 0) {
	    printf("couldn't recieve server message. terminating.");
	    exit(EXIT_FAILURE);
	  }

	  if (recv(client->conn.socket, client->response, MAX_BUFFER, 0) < 0) {
	    printf("couldn't recieve server message. terminating.");
	    exit(EXIT_FAILURE);
	  }
    printf("server response: %s\n", client->response);
  }
}
