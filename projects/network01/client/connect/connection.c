/*---------------------------------------------------------------------------------------------------------------CONNECTION
Dealing with Client connection.                                                                                                
-------------------------------------------------------------------------------------------------------------------------*/
#include <stdlib.h>
#include "../system/error.h"
#include "../system/scanner.h"
#include "connection.h"

static void client_create(clnt_t *client) {
/*Client socker being created.*/

  Render_Header("CONNECT", "Q(oo)-o");
  System_Message("creating socket");

  client->sock_desc = socket(AF_INET, SOCK_STREAM, 0);
  if (client->sock_desc < 0) {
    System_Message("failed to create socket.");
    exit(EXIT_FAILURE);
  }
  return;
}

static void client_binder(clnt_t *client, const char *ADDRESS, const char *PORT_STR) {
/*Client's socket being binder to the server.*/

  System_Message("binding server to socket.");

  uint32_t PORT = atoi(PORT_STR);

  client->server_address.sin_addr.s_addr = inet_addr(ADDRESS);
  client->server_address.sin_family = AF_INET;
  client->server_address.sin_port = htons(PORT);
   
  int32_t conn = connect(
    client->sock_desc, (struct sockaddr *) &client->server_address, sizeof(client->server_address));

  if (conn < 0) {
    System_Message("failed connect to server. Address, port or both is incorrect.");
    exit(EXIT_FAILURE);
  }
  return;
}

void client_connect(clnt_t *client, const char *ADDRESS, const char *PORT_STR) {
/*Wraps the  previous static functions. If nothing has failed the client tells who he or she is. The plan is it
 *implement this as a part of a validation-process in the future. Password-part unnecessary at the moment.*/

  client_create(client);
  client_binder(client, ADDRESS, PORT_STR);
  
  Render_Header("CLIENT", "You've been connected! Please enter username");
  client->size_user = scan_driver(ASCI_PLUG, 512, client->username, "select");
  return;
}
