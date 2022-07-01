#ifndef CONNECT_H
#define CONNECT_H

#include "controller.h"
#include "session.h"

#define CONN_ 0
#define LOGN_ 1
#define SIGN_ 2
#define VALD_ 3
#define DONE_ 4
#define EXIT_ 5

#define Message_Login_Succ(usr) printf("\tWelcome back, %s!\n", usr);
#define Message_Login_Fail(usr) printf("\tWrong username or/and password. Are you really '%s'\n?", usr);
#define Message_Setup_Succ(usr) printf("\tYour account has been created %s!\n", usr);
#define Message_Setup_Fail(usr) printf("\tSeems username '%s' already is taken, try another one\n", usr);

int8_t connect_create(client_t *client, char *address, int32_t port);
int8_t connect_driver(client_t *client, char *address, int32_t port);

static inline int8_t connect_setup_check(client_t *client) {
  if (client->socket_client < 0) {
    System_Message("failed to create socket");
    return EXIT_;
  } else if (client->socket_status < 0) {
    System_Message("failed connect to server");
    return EXIT_;
  }
  return SUCC;
}

static inline int8_t scanner_size_check(client_t *client) {
  if (client->size_user < 1 || client->size_pass < 1 ) {
    System_Message("something went south while scanning username and/or password");
    return EXIT_;
  }
  return SUCC;
}  
static inline int8_t connect_send_check(client_t *client) {
  if (client->size_send != client->size_pack) {
    System_Message("size_send not of same value as size_pack");
    return EXIT_;
  }
  return SUCC;
}

static inline int8_t protocol_obtain_check(client_t *client) {
  if (!check_term(client->pack, client->size_pack)) {
    System_Message("package not nullterminated");
    return EXIT_;
  }
  return SUCC;
}
#endif