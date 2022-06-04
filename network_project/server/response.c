/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                  RESPONSE
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/

#include "response.h"

/*

    memset(client_request, '\0', MAX_BUFFER);
    memset(server_response, '\0', MAX_BUFFER);

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
*/
