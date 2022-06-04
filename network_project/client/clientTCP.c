/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                CLIENT TCP
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "command.h"

#define MAX_BUFFER 4096

//socket create.
short socket_create(void) {
  short client_socket;
  printf("Create the socket\n");
  client_socket = socket(AF_INET, SOCK_STREAM, 0);
  return client_socket;
}

//socket connect.
int socket_connect(int hSocket) {

  int iRetval=-1;
  int ServerPort = 90190;
  struct sockaddr_in remote= {0};
  remote.sin_addr.s_addr = inet_addr("127.0.0.1"); //Local Host
  remote.sin_family = AF_INET;
  remote.sin_port = htons(ServerPort);
  iRetval = connect(hSocket,(struct sockaddr *)&remote,sizeof(struct sockaddr_in));
  return iRetval;
}

// Send the data to the server and set the timeout of 20 seconds

int socket_send(int client_socket,char* Rqst,short lenRqst) {

  int shortRetval = -1;
  struct timeval tv;
  tv.tv_sec = 20;  /* 20 Secs Timeout */
  tv.tv_usec = 0;
  if (setsockopt(client_socket,SOL_SOCKET,SO_SNDTIMEO,(char *)&tv,sizeof(tv)) < 0) {
    printf("Time Out\n");
    return -1;
  }
  shortRetval = send(client_socket, Rqst, lenRqst, 0);
  return shortRetval;
}
//receive the data from the server
int socket_recieve(int hSocket,char* Rsp,short RvcSize) {

    int shortRetval = -1;
    struct timeval tv;
    tv.tv_sec = 20;  /* 20 Secs Timeout */
    tv.tv_usec = 0;
    if(setsockopt(hSocket, SOL_SOCKET, SO_RCVTIMEO,(char *)&tv,sizeof(tv)) < 0) {
      printf("Time Out\n");
        return -1;
    }
    shortRetval = recv(hSocket, Rsp, RvcSize, 0);
    printf("Response %s\n",Rsp);
    return shortRetval;
}
//main driver program
int main(int argc, char *argv[]) {

  int client_socket, read_size;
  struct sockaddr_in server;
  char request[MAX_BUFFER] = {0};
  char respond[MAX_BUFFER] = {0};
  //Create socket
  client_socket = socket_create();
  if(client_socket == -1) {
    printf("Could not create socket\n");
    return 1;
  }

  printf("Socket is created\n");
  //Connect to remote server
  if (socket_connect(client_socket) < 0) {
    perror("connect failed.\n");
    return 1;
  }

  printf("Sucessfully conected with server\n");

  printf("Enter the Message: ");

  size_t send_length = command_driver(request);

  //Send data to the server
  socket_send(client_socket, request, send_length);

  //Received the data from the server

  read_size = socket_recieve(client_socket, respond, MAX_BUFFER);
  printf("Server Response : %s\n\n",respond);

  close(client_socket);
  shutdown(client_socket,0);
  shutdown(client_socket,1);
  shutdown(client_socket,2);
  return 0;
}
