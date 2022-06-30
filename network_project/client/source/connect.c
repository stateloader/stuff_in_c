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

static int8_t connect_scan(conn_item *items, size_t size_array) {

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

  client->size_user = scan_driver(client->user, SBUFF, "username");
  client->size_pass = scan_driver(client->pass, SBUFF, "password");

  return scanner_size_check(client->size_user, client->size_pass);
}

static int8_t connect_login(client_t *client) {
  Render_Header("LOGIN  ", "Connecting to server");

  if(!scan_userdata(client)) return EXIT_;

  client->protocol[SBYTE] |= (1 << LOGIN);

  return VALD_;
}

static int8_t connect_signp(client_t *client) {
  Render_Header("SIGNUP   ", "Connecting to server");

  if( !scan_userdata(client)) return EXIT_;

  client->protocol[SBYTE] |= (1 << SETUP);

  return VALD_;
}

static int8_t canonical_package(client_t *client) {

  client->size_pack = (client->size_user + client->size_pass + POFFS);

  client->user[client->size_user - 1] = DELIM;
  client->pass[client->size_pass - 1] = DELIM;

  strncat(client->pack, client->user, client->size_pack);
  strncat(client->pack, client->pass, client->size_pack);

  return protocol_append(client->pack, client->size_pack, client->protocol);
}

static int8_t connect_valid(client_t *client) {

  if (!canonical_package(client)) return EXIT_;

  Message_Info(client->pack);

  int32_t size_send = send(client->socket_client, client->pack, client->size_pack, 0);
  int32_t size_recv = recv(client->socket_client, client->recv, FBUFF, 0);

  Message_Info(client->recv);

  return DONE_;
}

static int8_t connect_setup(client_t *client, char *address, int32_t port) {
  Render_Header("CONNECT   ", "Connecting to server");

  client->socket_client = socket_create();
  client->socket_status = socket_connect(client->socket_client, address, port);

  client->protocol[TBYTE] = 0x80;
  client->protocol[ABYTE] = 0x80;
  client->protocol[SBYTE] = 0x80;
  
  return SUCC;
}

int8_t connect_driver(client_t *client, char *address, int32_t port) { 

  int8_t result = 0;

  result = connect_setup(client, address, port);
  if (result != SUCC) return result;

  while (state != DONE_) {
    switch(state) {
    case CONN_:
      state = connect_scan(conn_items, ARRAY_SIZE(conn_items));
      break;
    case LOGN_:
      state = connect_login(client);
      break;
    case SIGN_:
      state = connect_signp(client);
      break;
    case VALD_:
      state = connect_valid(client);
      break;
    }
    if (state == EXIT_) return EXIT;
  }

  return SUCC;
}