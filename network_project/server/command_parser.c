#include "command_parser.h"

void parse_client_command(char * client_command, char *server_response) {

  printf("Msg from client: %s\n", client_command);

  for (int i = 0; i < MAX_COMMAND; i++) {
    if (client_command[i] == 'T') {
      strcpy(server_response, "you've written something T-ish");
      return;
    }
  }
  strcpy(server_response, "you haven't written any T-ish");
  return;
}