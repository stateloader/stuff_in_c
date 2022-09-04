/*------------------------------------------------------------------------------------------CONNECT
Logic for client-connection.
-------------------------------------------------------------------------------------------------*/
#include <stdlib.h>
#include "../jackIO/scanner.h"
#include "connect.h"

static void client_create(cent_t *client) {
/*A client socket being created.*/

  Render_Header("CONNECT", "Q(oo)-o");
  System_Message("creating socket");

  client->sock_desc = socket(AF_INET, SOCK_STREAM, 0);
  if (client->sock_desc < 0) {
    System_Message("failed to create socket.");
    exit(EXIT_FAILURE);
  }
  return;
}

static void client_binder(cent_t *client, const char *ADDRESS, const char *PORT_STR) {
/*Client's socket binds to the server.*/

  System_Message("binding server to socket.");

  uint32_t PORT = atoi(PORT_STR);

  client->server_address.sin_addr.s_addr = inet_addr(ADDRESS);
  client->server_address.sin_family = AF_INET;
  client->server_address.sin_port = htons(PORT);
   
  int32_t conn = connect(
    client->sock_desc, (struct sockaddr *) &client->server_address,
    sizeof(client->server_address)
  );

  if (conn < 0) {
    System_Message("failed connect to server. Address, port or both is incorrect.");
    exit(EXIT_FAILURE);
  }
  return;
}

cent_t client_connect(const char *ADDRESS, const char *PORT_STR) {
/*Wraps the previous functions. The client tells who she or he is if nothing fails. The plan is
 *to implement some sort of validation-process in the future.*/

  cent_t client = {0};
  client_create(&client);
  client_binder(&client, ADDRESS, PORT_STR);
  Render_Header("CLIENT", "You've been connected! Please enter username");
  client.size_user = scan_driver(ASCI_PLUG, 512, client.username, "username");
  return client;
}
