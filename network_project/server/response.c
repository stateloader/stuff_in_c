/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                  RESPONSE
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/socket.h>
#include "response.h"

static void incoming(int client_socket, char *request) {

  recv(client_socket, request, MAX_BUFFER, 0);
  printf("client request: %s\n", request);
}

static void outgoing(int client_socket, char *response) {

  char ADELE_IT_IS[MAX_BUFFER] = \

		"So hello from the other side (other side)\n" \
		"I must've called a thousand times (thousand times)\n" \
		"To tell you I'm sorry for everything that I've done\n" \
		"But when I call, you never seem to be home\n\n" \

		"Hello from the outside (outside)\n" \
		"At least I can say that I've tried (I've tried)\n" \
		"To tell you I'm sorry for breaking your heart\n" \
		"But it don't matter, it clearly doesn't tear you apart anymore\n\n";

  strcpy(response, ADELE_IT_IS);
  send(client_socket, response, strlen(response), 0);
}

void response_driver(int client_socket, char *request, char *response) {

  incoming(client_socket, request);
  memset(request, '\0', MAX_BUFFER);

  outgoing(client_socket, response);
  memset(response, '\0', MAX_BUFFER);
}
