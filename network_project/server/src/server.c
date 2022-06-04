/*------------------------------------------------------------------------------------------------------------------------
                                                                                                             SERVER MODULE
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/
#include "scan.h"
#include "server.h"

static void init_portip(conn_t *conn, char *address, int port) {

  conn->server.sin_family = AF_INET;
  conn->server.sin_port = htons(port);
  conn->server.sin_addr.s_addr = inet_addr(address);
  printf("address and port established")
}

static void init_socket(conn_t *conn) {

  conn->socket = socket(AF_INET, SOCK_STREAM, 0);

  if (conn->socket < 0) {
    printf(" but couldn't create a socket\n\nterminating.\n");
    exit(EXIT_FAILURE);
  }
  printf(" and a socket created");
  conn->state |= (1 << SOCK);
}

static void init_bind(conn_t *conn) {

  if (connect(conn->socket, (struct sockaddr *)&conn->server, sizeof(conn->server)) < 0) {
		printf(" witch unfortunately faild to bind.\nsure ip and/or port is correct?\n\nterminating.");
    exit(EXIT_FAILURE);
  }
  printf(" which was successfully binded to the server. Let's boogie!\n\n");
  conn->state |= (1 << BIND);
}

conn_t setup_connection(char *address, int port, uint8_t *state) {

  conn_t conn;

  init_portip(&conn, address, port);

  init_socket(&conn);
  *state |= (1 << SOCK);

  init_connection(&conn);
  *state |= (1 << CONN) | (1 << CMND);

  return conn;
}

void server_session(serv_t *server) {

	for (;;) {

	  if (recv(server->conn.socket_desc, server->incoming, MAX_BUFFER, 0) < 0) {
	    printf("couldn't recieve server message. terminating.");
	    exit(EXIT_FAILURE);
	  }

	  if (send(server->conn.socket_desc, server->outgoing, server->length, 0) < 0) {
	    printf("couldn't recieve server message. terminating.");
	    exit(EXIT_FAILURE);
	  }

    memset(server->incoming, '\0', MAX_BUFFER);
    memset(server->outgoing, '\0', MAX_BUFFER);
  }
}



/*
  int socket_desc, client_sock, client_size;
  struct sockaddr_in server_addr, client_addr;
  char server_message[2000], client_message[2000];
  
  // Clean buffers:
  memset(server_message, '\0', sizeof(server_message));
  memset(client_message, '\0', sizeof(client_message));
  
  // Create socket:
  socket_desc = socket(AF_INET, SOCK_STREAM, 0);
  
  if(socket_desc < 0){
      printf("Error while creating socket\n");
      return -1;
  }
  printf("Socket created successfully\n");

  // Set port and IP:
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(2000);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  
  // Bind to the set port and IP:
  if(bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr))<0){
      printf("Couldn't bind to the port\n");
      return -1;
  }
  printf("Done with binding\n");
  
  // Listen for clients:
  if(listen(socket_desc, 1) < 0){
      printf("Error while listening\n");
      return -1;
  }
  printf("\nListening for incoming connections.....\n");

  while(1) {
      // Accept an incoming connection:
    client_size = sizeof(client_addr);
    client_sock = accept(socket_desc, (struct sockaddr*)&client_addr, &client_size);
    
    if (client_sock < 0){
        printf("Can't accept\n");
        return -1;
    }
    printf("Client connected at IP: %s and port: %i\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    
    // Receive client's message:
    if (recv(client_sock, client_message, sizeof(client_message), 0) < 0){
        printf("Couldn't receive\n");
        return -1;
    }

    parse_client_command(client_message, server_message);    

    if (send(client_sock, server_message, strlen(server_message), 0) < 0){
        printf("Can't send\n");
        return -1;
    }
    close(client_sock);
  }
  // Closing the socket:
  close(socket_desc);
  
*/
