/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                SERVER TCP
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "socket.h"

#define MAX_BUFFER 4096

int main(int argc, char *argv[]) {

  int server_socket = 0;
  int client_length = 0;
  int client_socket = 0;

  struct sockaddr_in server_address;
  struct sockaddr_in client_address;

  char client_request[MAX_BUFFER] = {0};
  char server_response[MAX_BUFFER] = {0};

  socket_create(&server_socket);
  socket_bind(server_socket, &server_address, "127.0.0.1", 90190);
  socket_listen(server_socket);

  while(1) {

    memset(client_request, '\0', MAX_BUFFER);
    memset(server_response, '\0', MAX_BUFFER);
		socket_accept(server_socket, &client_socket, &client_address);

    if (recv(client_socket, client_request, MAX_BUFFER, 0) < 0) {
      printf("recv failed");
      break;
    }
    printf("client request: %s\n", client_request);
    if (strcmp("-temperature", client_request) == 0) {
      strcpy(server_response,"Hi there !");
    } else {
      strcpy(server_response,"Invalid Message !");
    }
    if (send(client_socket, server_response, strlen(server_response), 0) < 0){
      printf("Send failed");
      return 1;
    }
    close(client_socket);
    sleep(1);
  }
  return 0;
}
