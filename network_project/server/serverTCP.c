#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "socket.h"

#define MAX_BUFFER 4096

int main(int argc, char *argv[]) {

  struct sockaddr_in client_address;

  char client_request[MAX_BUFFER]= {0};
  char server_respond[MAX_BUFFER] = {0};
  
  int server_socket = socket_create();

  socket_bind(server_socket, "127.0.0.1", 90190);
  listen(server_socket, 3);

  while(1) {

    int client_size = sizeof(client_address);
    printf("check-- client_size: %d\n", client_size);
    int client_socket = accept(server_socket, (struct sockaddr*) &client_address, (socklen_t*) &client_size);
    
    printf("Client connected at IP: %s and port: %i\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));
    
    memset(client_request, '\0', MAX_BUFFER);
    memset(server_respond, '\0', MAX_BUFFER);

    if (recv(client_socket, client_request, MAX_BUFFER, 0) < 0) {
      printf("recv failed");
      break;
    }

    if (strcmp("-temperature", client_request) == 0) {
      strcpy(server_respond,"Hi there !");
    } else {
      strcpy(server_respond,"Invalid Message !");
    }
    if (send(client_socket, server_respond, strlen(server_respond), 0) < 0){
      printf("Send failed");
      return 1;
    }
    close(client_socket);
    sleep(1);
  }
  return 0;
}
