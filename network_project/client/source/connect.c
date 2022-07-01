/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                   CONNECT
--------------------------------------------------------------------------------------------------------------------------
I really wanted to implement the functionality in this module in the BROWSER - "all userinput in one place" but it turned
out (etc, koda vidare nu istä'llet)
------------------------------------------------------------------------------------------------------------------------*/

#include "cstring.h"
#include "scanner.h"
#include "connect.h"

static int8_t state = CONN_;

typedef int8_t (conn_func)(client_t *client);

typedef struct ConnectItem {
  const uint8_t this_state;
  const uint8_t next_state;
  const char *cmnd;
} conn_item;

static conn_item conn_items[] = {
  {CONN_, LOGN_, "-login"},
  {CONN_, SIGN_, "-signup"},
  {CONN_, EXIT_, "-exit"}
};
//conn_items handy while jumping between states in the 'connect_driver'

static void protocol_restore(client_t *client) {
/*Restores, "default", the protocol where the highest bit always is set.*/

  client->protocol[TBYTE] = 0x80;
  client->protocol[ABYTE] = 0x80;
  client->protocol[SBYTE] = 0x80;
}

static int8_t protocol_obtain(client_t *client) { 
/*Assigns the protocol by copy received (latest) received protocol.*/

  client->protocol[TBYTE] = client->recv[client->size_recv - 4];
  client->protocol[ABYTE] = client->recv[client->size_recv - 3];
  client->protocol[SBYTE] = client->recv[client->size_recv - 2];

  return protocol_obtain_check(client);
}

static int8_t connect_create_package(client_t *client) {
/*Creates a canonical package before throwing it at the server.*/

  client->size_pack = (client->size_user + client->size_pass + POFFS);

  client->user[client->size_user - 1] = DELIM;
  client->pass[client->size_pass - 1] = DELIM;

  strncat(client->pack, client->user, client->size_pack);
  strncat(client->pack, client->pass, client->size_pack);

  client->user[client->size_user - 1] = '\0';
  client->pass[client->size_pass - 1] = '\0';

  return protocol_append(client->pack, client->size_pack, client->protocol);
}

static int8_t connect_scan(conn_item *items, size_t size_array) {
/*Array of possible choices being printed. "Connect Menu". User choose by mimic one of the choices.*/

  for (size_t i = 0; i < size_array; i++)
    printf("\t\t\t%s\n", items[i].cmnd);

  char command[SBUFF] = {'\0'};
  size_t cmnd_size = scan_driver(command, SBUFF, "select");

  for (size_t i = 0; i < size_array; i++) {
    if (string_comp(command, items[i].cmnd, cmnd_size)) {
      return items[i].next_state;
    }
  }
  Message_Info("Not an option. try again");
  return state;
}

static int8_t scan_userdata(client_t *client) {
/*Input of username and password, login as in setup-mode.*/

  client->size_user = scan_driver(client->user, SBUFF, "username");
  client->size_pass = scan_driver(client->pass, SBUFF, "password");

  return scanner_size_check(client);
}

static int8_t connect_login(client_t *client) {
/*Bit LOGIN being set in SBYTE. When reveived it tells the server to init login-logic.*/
 
  Render_Header("LOGIN  ", "Connecting to server");

  if (!scan_userdata(client)) return EXIT_;
  client->protocol[SBYTE] |= (1 << LOGIN);

  return VALD_;
}

static int8_t connect_setup(client_t *client) {
/*Bit SETUP being set in SBYTE. When reveived it tells the server to init setup-logic.*/
  
  Render_Header("SIGNUP   ", "Connecting to server");

  if (!scan_userdata(client)) return EXIT_;
  client->protocol[SBYTE] |= (1 << SETUP);

  return VALD_;
}

static int8_t connect_result(client_t *client) {

  if (client->protocol[SBYTE] & (1 << VALID)) {
    if (client->protocol[SBYTE] & (1 << LOGIN)) {
      Message_Login_Succ(client->user);
      return DONE_;
    } else if (client->protocol[SBYTE] & (1 << SETUP)) {
      Message_Setup_Succ(client->user);
      return DONE_;
    } else {
      Message_Info("Shouldn't be here, (positive connect result)");
      return EXIT_;
    }
  } else {
    if (client->protocol[SBYTE] & (1 << LOGIN)) {
      Message_Login_Fail(client->user);
      return CONN_;
    } else if (client->protocol[SBYTE] & (1 << SETUP)) {
      Message_Setup_Fail(client->user);
      return CONN_;
    } else {
      Message_Info("Shouldn't be here, (negative connect result)");
      return EXIT_;
    }
  }
}

static int8_t connect_valid(client_t *client) {
/*Here, the user has entered a username and password in order to login/signup which being sent and dealt
 *with by the server. If ok, we're DONE and are able to have the time of our lives. Else we're thrown
 *back to state CONN_ (mening try again).*/

  int8_t result = 0;

  result = connect_create_package(client);
  if (result != SUCC) return result;

  client->size_send = send(client->socket_client, client->pack, client->size_pack, 0);
  result = connect_send_check(client);
  if (result != SUCC) return result;

  client->size_recv = recv(client->socket_client, client->recv, FBUFF, 0);
  result = protocol_obtain(client);
  if (result != SUCC) return result;

  return connect_result(client);
}

 int8_t connect_create(client_t *client, char *address, int32_t port) {
/*Connecting to server.*/
  Render_Header("CONNECT   ", "Connecting to server");

  client->socket_client = socket_create();
  client->socket_status = socket_connect(client->socket_client, address, port);

  return connect_setup_check(client);
}

int8_t connect_driver(client_t *client, char *address, int32_t port) { 
/*While the user hasn't made any progress in being validated by the server or typed exit the loop will continue.*/

  int8_t result = connect_create(client, address, port);
  if (result != SUCC) return result;

  while (state != DONE_) {
    switch(state) {
    case CONN_:
      protocol_restore(client);
      Render_Header("VALIDATE ", "Validate ipsum dolor sit amet, consectetur adipiscing elit");
      state = connect_scan(conn_items, ARRAY_SIZE(conn_items));
      break;
    case LOGN_:
      state = connect_login(client);
      break;
    case SIGN_:
      state = connect_setup(client);
      break;
    case VALD_:
      state = connect_valid(client);
      break;
    }
    if (state == EXIT_) return EXIT;
  }
  return SUCC;
}