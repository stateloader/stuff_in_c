#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#define MAX_BUFFER 4096
#define PORT 2000
#define SA struct sockaddr

void respond(int connfd) {
  for (;;) {

    char incoming[MAX_BUFFER];
    char outgoing[MAX_BUFFER];
    memset(incoming, '\0', MAX_BUFFER);
    memset(outgoing, '\0', MAX_BUFFER);

    recv(connfd, incoming, MAX_BUFFER, 0);

    printf("from client: %s\n", incoming);

    char *response = "hundra grader";
    strcpy(outgoing, response);
    send(connfd, outgoing, MAX_BUFFER, 0);
  }
}

int main() {

  int sockfd, connfd, len;
  struct sockaddr_in servaddr, cli;

  // socket create and verification
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    printf("socket creation failed...\n");
    exit(0);
  }
  else
      printf("Socket successfully created..\n");
  bzero(&servaddr, sizeof(servaddr));

  // assign IP, PORT
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(PORT);

  // Binding newly created socket to given IP and verification
  if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
    printf("socket bind failed...\n");
    exit(0);
  }
  else
      printf("Socket successfully binded..\n");

  // Now server is ready to listen and verification
  if ((listen(sockfd, 5)) != 0) {
    printf("Listen failed...\n");
    exit(0);
  }
  else
    printf("Server listening..\n");
  len = sizeof(cli);

  connfd = accept(sockfd, (SA*)&cli, &len);
  if (connfd < 0) {
    printf("server accept failed...\n");
    exit(0);
  }
  else
    printf("server accept the client...\n");
  respond(connfd);
}
