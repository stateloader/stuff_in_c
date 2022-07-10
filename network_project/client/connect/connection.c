/*---------------------------------------------------------------------------------------------------------------Connection
Dealing with Client connection.                                                                                                
-------------------------------------------------------------------------------------------------------------------------*/
#include <stdlib.h>
#include "../system/error.h"
#include "../system/scanner.h"
#include "connection.h"

static const char *ADDRESS = "127.0.0.1";
static const int32_t PORT = 90190;

static void client_create(clnt_t *client) {
/*Client socker being created.*/
  System_Message("Creating socket");

  client->sock_desc = socket(AF_INET, SOCK_STREAM, 0);
  if (client->sock_desc < 0) {
    System_Message("Failed to create socket.");
    exit(EXIT_FAILURE);
  }
  return;
}

static void client_binder(clnt_t *client) {
/*Client's socket being binder to the server. Handshake bit under the hood.*/
  System_Message("Binding server to socket.");

  client->server_address.sin_addr.s_addr = inet_addr(ADDRESS);
  client->server_address.sin_family = AF_INET;
  client->server_address.sin_port = htons(PORT);
   
  client->conn_stat = connect(
    client->sock_desc, (struct sockaddr *) &client->server_address, sizeof(client->server_address));

  if (client->conn_stat < 0) {
    System_Message("Failed connect to server.");
    exit(EXIT_FAILURE);
  }
  return;
}

void client_connect(clnt_t *client) {
/*Wraps the  previous static functions. If nothing has failed the client tells who he or she is. The plan is it
 *implement this as a part of a validation-process in the future. Password-part unnecessary at the moment.*/

  client_create(client);
  client_binder(client);
  
  Render_Header("CONFIRM", "Enter username and password");
  client->size_user = scan_driver(client->username, "username", SBUFF);
  client->size_pass = scan_driver(client->password, "password", SBUFF);
}