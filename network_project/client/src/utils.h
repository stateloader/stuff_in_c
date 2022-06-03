#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAX_BUFFER 4096

#define check_term(str, len) (str[len - 1] == '\0')

#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

/*
void print_byte(uint8_t byte) {
  for (uint8_t i = 1 << 7; i > 0; i = i / 2)
    (byte & i) ? printf("1") : printf("0");
}
*/



/*
static void request(cent_t *client) {

  ssize_t status = 0;
  while (status == 0)
    status = send(client->conn.socket, client->command, MAX_BUFFER, 0);

  if (status < 0) {
    printf("couldn't sent message to server. terminating.\n");
    exit(EXIT_FAILURE);
  }
  client->state &= ~(1 << RQST);
  client->state |= (1 << RECV);
}

static void recieve(cent_t *client) {

  ssize_t status = recv(client->conn.socket, client->response, MAX_BUFFER, 0);
  if (status < 0) {
    printf("couldn't recieve server message. terminating.");
    exit(EXIT_FAILURE);
  } else if (status > 0) {
    printf("server response: %s\n", client->response);
    client->state &= ~(1 << RECV);
    client->state |= (1 << CMND);
  } else {
    ;
  }
}
*/

//  if (client->state &= RQST)
 //   request(client);
  //if (client->state &= RECV)
  //  recieve(client);
#endif
