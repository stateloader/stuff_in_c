#ifndef RESPONSE_H_
#define RESPONSE_H_

#define MAX_BUFFER 4096

void response_driver(int client_socket, char *request, char *response);

#endif
