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

#define set_state(byte, bit) byte |= (1 << bit)
#define get_state(byte, bit) byte &= (1 << bit)
#define tog_state(byte, bit) byte ^= (1 << bit)
#define clr_state(byte, bit) byte &= ~(1 << bit)

#define check_term(str, len) (str[len - 1] == '\0')

#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

/*
void print_byte(uint8_t byte) {
  for (uint8_t i = 1 << 7; i > 0; i = i / 2)
    (byte & i) ? printf("1") : printf("0");
}
*/


/*
static void client_request(cent_t *client, char *message) {

  scan_t scan = scan_driver(message);
  comreq_checker(client, &scan);

  if (send(client->conn.socket, client->request, client->sizereq, 0) < 0){
    printf("couldn't sent message to server. terminating.\n");
    exit(EXIT_FAILURE);
 	}
  memset(client->request, '\0', MAX_BUFFER);
}

static void server_response(cent_t *client) {

  if (recv(client->conn.socket, client->response, MAX_BUFFER, 0) < 0){
    printf("couldn't recieve server message. terminating.");
    exit(0);
  }
  printf("from server: %s\n", client->response);
  memset(client->response, '\0', MAX_BUFFER);
}



 // client_request(client, "skriv natt kul: ");
  //server_response(client);

//  close(client->conn.socket);

}

  switch(PHASE) {
  case START:
    PHASE = option_start(command);
    break;
  case FETCH:
    PHASE = option_fetch(command);
    break;
  case STEER:
    PHASE = option_steer(command);
  }

  return option_items[PHASE].func(command);


static void option_start(char *command, uint8_t *state) {																	// incl view

	scan_t scan = scan_driver("select");
  string_copy(command, scan.scanner, scan.length);
}

static void option_fetch(char *command, uint8_t *state) {																	// incl view

  scan_t scan = scan_driver("select");
  *state ^= (1 << CMND);
}

static void option_steer(char *command, uint8_t *state) {																	// incl view

  scan_t scan = scan_driver("select");
  *state ^= (1 << CMND);
}

static option_item option_items[] = {
  {option_start},{option_fetch},{option_steer}
}
*/

#endif
