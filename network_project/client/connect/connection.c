/*---------------------------------------------------------------------------------------------------------------Connection
Macros implemented reg                                                                                                   
-------------------------------------------------------------------------------------------------------------------------*/
#include <sys/socket.h>
#include <arpa/inet.h>
#include "connection.h"
#include "socket.h"
#include "../system/error.h"
#include "../command/scanner.h"
#include "connection.h"


static void connect_checks(conn_t *connect, uint8_t *state, uint16_t *error) {

  if (connect->sock_desc < 0) {
    *state |= (1 << ERROR); *error |= (1 << SOERR);
  }// Failed to create socket.

  if (connect->bind_stat < 0) {
    *state |= (1 << ERROR); *error |= (1 << COERR);
  }// Falied to connect to server.
}

void connect_driver(conn_t *connect, uint8_t *state, uint16_t *error) {

  Render_Header("CONNECT   ", "Connecting to server");

  connect->sock_desc = socket_create();
  connect->bind_stat = socket_connect(connect->sock_desc, "127.0.0.1", 90190);

  connect_checks(connect, state, error);
  if (*state & (1 << ERROR)) return;

  *state |= (1 << CONNF);
  return;
}

void package_send(uint32_t sock_desc, char *package, size_t size_pack, uint8_t *state, uint16_t *error) {

  size_t size_send = send(sock_desc, package, size_pack, 0);

  if (size_send != size_pack) {
    *state |= (1 << ERROR); *error |= (1 << RSERR);
    return;
  }// Size on send and package differ; "Failed to send package" - call.

  System_Message("Package sent.");
  return;
}

size_t package_recv(uint32_t sock_desc, char *package, uint8_t *state, uint16_t *error) {

  size_t size_recv = recv(sock_desc, package, RBUFF, 0);

  if (size_recv < 4) {
    *state |= (1 << ERROR); *error |= (1 << RRERR);
    return size_recv;
  }// Size recv is under 4 bytes, meaning the least possible size of a response failed.

  System_Message("Package received.");
  return size_recv;
}
