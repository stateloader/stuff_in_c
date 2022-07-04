/*-----------------------------------------------------------------------------------------------------------SERVER SOCKET
                                                                                                            
------------------------------------------------------------------------------------------------------------------------*/

#include "socket.h"

int8_t socket_create(int *server_socket) {
  System_Message("creating socket");
  *server_socket = socket(AF_INET, SOCK_STREAM, 0);
  return SUCC;
}

int8_t socket_binder(int server_socket, struct sockaddr_in *server_address, char *address, int port) {

  server_address->sin_addr.s_addr = inet_addr(address);
  server_address->sin_family = AF_INET;
  server_address->sin_port = htons(port);
  
  System_Message("server established");

  if (bind(server_socket, (struct sockaddr *) &(*server_address), sizeof(*server_address)) < 0) {
    printf("failed to bind port, ip. terminating.\n\n");
    return FAIL;
  }
  System_Message("binding successfull.\n");
  return SUCC;
}

int8_t socket_listen(int server_socket) {

  if (listen(server_socket, MAX_CLIENT) < 0) {
    System_Message("\nerror while listening\n");
    return FAIL;
  }
  return SUCC;
}

int8_t socket_accept(int server_socket, int *client_socket, struct sockaddr_in *client_address) {
  Render_Header("IDLE       ", "Waiting for incoming connections");

  int client_length = sizeof(*client_address);

  *client_socket = accept(server_socket, (struct sockaddr *) &(*client_address), (socklen_t*) &client_length);
  if (*client_socket < 0) {
    System_Message("\nerror while accepting client.\n");
    exit(EXIT_FAILURE);
  }
  Render_Header("CONNETION   ", "Client conneted");
  
  printf("\t\t\tClient connected at IP: %s and port: %i\n",
    inet_ntoa(client_address->sin_addr), ntohs(client_address->sin_port)
  );

  return SUCC;
}

int8_t socket_close(int client_socket) {
  close(client_socket);
  shutdown(client_socket, 0);
  shutdown(client_socket, 1);
  shutdown(client_socket, 2);

  return SUCC;
}