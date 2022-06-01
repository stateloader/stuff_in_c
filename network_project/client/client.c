#include "client.h"

#define MAX_COMMAND 2000


int main(void) {

  sess_t session = session_setup("192.168.0.101", 2000);
  
  char server_message[2000], client_message[MAX_COMMAND];

  memset(server_message,'\0',sizeof(server_message));
  memset(client_message,'\0',sizeof(client_message));

<<<<<<< HEAD
  // Create socket:
  socket_desc = socket(AF_INET, SOCK_STREAM, 0);

  if(socket_desc < 0){
      printf("Unable to create socket\n");
      return -1;
  }

  printf("Socket created successfully\n");

  // Set port and IP the same as server-side:
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(2000);
  server_addr.sin_addr.s_addr = inet_addr("192.168.0.101");

  // Send connection request to server:
  if (connect(socket_desc, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
=======
  if (connect(session.socket_desc, (struct sockaddr *)&session.server_addr, sizeof(session.server_addr)) < 0){
>>>>>>> 3d616b43c84642e226aeed01d3f2b12b0cd87f98
      printf("Unable to connect\n");
      return -1;
  }
  
  printf("Connected with server successfully\n");

  scan_t scan = scan_driver("enter message");

  if(send(session.socket_desc, scan.scanner, strlen(scan.scanner), 0) < 0){
      printf("Unable to send message\n");
      return -1;
  }

  if(recv(session.socket_desc, server_message, sizeof(server_message), 0) < 0){
      printf("Error while receiving server's msg\n");
      return -1;
  }

  printf("Server's response: %s\n",server_message);

  close(session.socket_desc);

  return 0;
}
