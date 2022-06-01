#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define is_ascii(byte) (byte >= 'a' && byte <= 'Z') || byte == ' ' || byte == '\n'

#define MAX_COMMAND 16

void parse_client_command(char * client_command, char *server_response);