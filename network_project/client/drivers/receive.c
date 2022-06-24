/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                  Response
--------------------------------------------------------------------------------------------------------------------------
info fasda
------------------------------------------------------------------------------------------------------------------------*/
#include "socket.h"
#include "receive.h"

void receive_driver(int32_t client_socket, recv_t *receive) {
  System_Message("Inside recieve driver");

  receive->size_recv = recv(client_socket, receive->recv, FBUFF, 0);
  System_Message(receive->recv);
}